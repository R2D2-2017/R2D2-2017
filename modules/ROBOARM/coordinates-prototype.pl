#!/usr/bin/env perl

# Author:    Chris Smeele
# Copyright: The R2D2 Team
# License:   See LICENSE
#
# This is a prototype for controlling the robot arm using coordinates.
# i.e. it translates X,Y coordinates into rotations for two of the three motors.
# The third dimension is omitted as it has no effect on the other planes.
#
# Depends on GD and perl 5.12 or higher.
# 'feh' is assumed to be an installed image viewer, replace if you like.

use 5.12.0;
use warnings;

use Math::Trig qw/ acos asin atan /;
use GD;

my $PI = Math::Trig::pi;

sub deg2rad { (shift) * ($PI/180) }
sub rad2deg { (shift) * (180/$PI) }

sub fmtpos { sprintf "(%5.1f, %5.1f)", @_ }

sub arm_get_positions {
    # Get position of joint 2 and the hand, based on the joint rotations.
    my %arm = @_;

    my @point1 = (
        $arm{len1} * cos($arm{rot1}),
        $arm{len1} * sin($arm{rot1}),
    );

    my @point2 = (
        # Joint 2's rotation relative to ground is independent from joint 1.
        $point1[0] + $arm{len2} * cos($arm{rot2}),
        $point1[1] + $arm{len2} * sin($arm{rot2}),
    );

    # Point 1 = joint 2
    # Point 2 = hand
    return (point1 => [@point1], point2 => [@point2]);
}

sub arm_move {
    # Move the arm to the given XY coordinates.
    # This updates the rot1 and rot2 properties of the arm.
    my $arm = shift;
    my @pos = @_;

    # We can't handle exact zero values very well...
    $_ ||= 0.001 for @pos;

    # Quality sketches!
    #
    #       o------<
    #      /  .. 
    #     /     ..
    #    /   _____.x
    #   o---' 
    #
    #   o-------o-------<
    #

    my $distance = sqrt($pos[0]**2 + $pos[1]**2);
    my $max_distance = $arm->{len1} + $arm->{len2};
    my $min_distance = abs $arm->{len2} - $arm->{len1};

    # Sanity checks.

    die "Provided point " . fmtpos(@pos) . " is out of reach "
        . sprintf("(distance assertion %.1f <= %.1f <= %.1f)\n", $min_distance, $distance, $max_distance)
          if $distance > $max_distance or $distance < $min_distance;

    # TODO: Add rotation limits.


    # Angle between position and ground.
    my $off_rot = atan($pos[1] / $pos[0]);

    # Make a triangle: base >---(distance)---< dest,   base >---(len1)---< A,   A >---(len2)---< dest.
    # Calculate the angle from base/ground to point A.
    my $rot1 = acos(($arm->{len1}**2 + $distance**2 - $arm->{len2}**2) / (2 * $arm->{len1} * $distance));
    # Calculate the angle from point A to dest.
    my $rot2 = acos(($arm->{len1}**2 + $arm->{len2}**2 - $distance**2) / (2 * $arm->{len1} * $arm->{len2}));

    # Tilt with the destination's angle.
    $rot1 += $off_rot;
    # rot2 was based on rot1, rebase it onto ground level.
    $rot2  = $rot1 - deg2rad(180) + $rot2;

    say "move to -> " . fmtpos(@pos)
        . " off(" . sprintf("%3.1f", rad2deg $off_rot)
        . ") rot: " . fmtpos(rad2deg($rot1), rad2deg($rot2))
        . sprintf(" dist<%.1f>", $distance);

    $arm->{rot1} = $rot1;
    $arm->{rot2} = $rot2;
}

sub dump_arm {
    my %arm = @_;
    say "joint2 @ " . fmtpos(@{{ arm_get_positions %arm }->{point1}})
      . ", hand @ " . fmtpos(@{{ arm_get_positions %arm }->{point2}});
}

sub show_arm {
    my %arm = @_;

    my $scale = 4; # Must be at least 3 to accommodate the font.
    my $im = new GD::Image($scale*100, $scale*100);

    # What are colors /really/ though.
    my $black = $im->colorAllocate(0x00, 0x00, 0x00);
    my $white = $im->colorAllocate(0xff, 0xff, 0xff);
    my $grey  = $im->colorAllocate(0xdd, 0xdd, 0xdd);
    my $red   = $im->colorAllocate(0xdd, 0x00, 0x00);
    my $green = $im->colorAllocate(0x00, 0xdd, 0x00);
    my $blue  = $im->colorAllocate(0x00, 0x00, 0xdd);

    # Background.
    $im->fill(0, 0, $white);

    # Draw grid.
    for my $r (0..10) {
        $im->line(0, $r*10*$scale, 10*10*$scale, $r*10*$scale, $grey);
        $im->line($r*10*$scale, 0, $r*10*$scale, 10*10*$scale, $grey);

        for my $c (0..10) {
            $im->filledRectangle($r*10*$scale-$scale/2,        $c*10*$scale - $scale/2,
                                 $r*10*$scale+$scale/2, $c*10*$scale + $scale/2,
                                 $grey);
        }
    }

    my %pos = arm_get_positions %arm;

    # Scale / translate to center of image.
    my $tl = sub { map { $_ * $scale } ($_[0] + 50, $_[1]) };

    $im->setThickness($scale);

    # Draw arm.
    $im->line($tl->(@{$arm{base}}),   $tl->(@{$pos{point1}}), $red);
    $im->line($tl->(@{$pos{point1}}), $tl->(@{$pos{point2}}), $green);

    $im->setPixel($tl->(@{$arm{base}}), $black);

    # Y coordinate 0 is at the top of the canvas. This is annoying.
    $im->flipVertical();

    $im->string(gdGiantFont, 2,  0, fmtpos(@{$pos{point1}}) . " - joint2", $red);
    $im->string(gdGiantFont, 2, 14, fmtpos(@{$pos{point2}}) . " - hand",   $green);
    $im->string(gdGiantFont, 2, 28, fmtpos(rad2deg($arm{rot1}), rad2deg($arm{rot2})) . " - rot (j1,j2)", $blue);
    $im->string(gdGiantFont, 2, 42, "grid cell = 10x10cm", $black);

    # Write directly to an image viewer.
    open my $feh, '|-', 'feh -' or die "$!";
    print $feh $im->png();
    close $feh;
    wait; # Wait for feh to die a slow and painful death.
}

my %arm = (
    base => [0, 0], # Not used.
    len1 => 18.5,   # Length of first arm part.
    len2 => 20,     # Length of second arm part.
    rot1 =>  0,     # Rotation of first joint. (from ground _ )
    rot2 =>  0,     # Rotation of second joint. (from ground _ ) -> Independent from rot1.
);

if (@ARGV == 2) {

    # Show arm position/rotation for the X and Y provided on the command line.

    arm_move(\%arm, $ARGV[0], $ARGV[1]); dump_arm %arm; show_arm %arm;

} elsif (@ARGV) {
    die "usage: $0 [x y]\n";

} else {
    dump_arm %arm; show_arm %arm;

    # Some tests.
    arm_move(\%arm, 10, 20); dump_arm %arm; show_arm %arm;
    arm_move(\%arm, 20, 10); dump_arm %arm; show_arm %arm;
    arm_move(\%arm, 28, 12); dump_arm %arm; show_arm %arm;
    arm_move(\%arm, 10,  5); dump_arm %arm; show_arm %arm;
    arm_move(\%arm, 15, 10); dump_arm %arm; show_arm %arm;
    arm_move(\%arm, 20,  0); dump_arm %arm; show_arm %arm;
    arm_move(\%arm,  9,  0); dump_arm %arm; show_arm %arm;
    arm_move(\%arm,  4,  0); dump_arm %arm; show_arm %arm;
}
