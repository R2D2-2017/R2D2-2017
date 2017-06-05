#include "ky101.hh"

Ky101::Ky101(hwlib::target::pin_in &signal) : signal(signal) {}

bool Ky101::get() {
  if (signal.get()) {
    return 1;
  }
  return 0;
}