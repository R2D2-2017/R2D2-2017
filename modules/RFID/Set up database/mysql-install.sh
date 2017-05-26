
#Always good to update everything
sudo apt-get update && sudo apt-get upgrade

#Installation of mysql server and phpmyadmin for easy management
sudo apt-get install mysql-server phpmyadmin
sudo mysql_secure_installation
sudo mysql_install_db