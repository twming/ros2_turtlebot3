# software_setup
software setup for ROS and docker

### Enable SSH
```
sudo nano /etc/ssh/sshd_config.d/60-cloudimg-settings.conf
```
```
PasswordAuthentication yes
```
### Disable Auto Background Update
```
sudo nano /etc/apt/apt.conf.d/20auto-upgrades
```
```
APT::Periodic::Update-Package-Lists "0";
APT::Periodic::Unattended-Upgrade "0";
```
### Stop the Network Wait, Suspend, Sleep
```
sudo systemctl mask systemd-networkd-wait-online.service
sudo systemctl mask sleep.target suspend.target hibernate.target hybrid-sleep.target
```
