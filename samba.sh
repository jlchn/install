sudo apt-get install smbclient

sudo apt-get install cifs-utils


# get sharing dir on remote host 192.168.0.103, /Public in this example
smbclient -L 192.168.0.103 -N 

# create a dir for mounting the remote dir
sudo mkdir /mnt/samba 
# -t cifs means using SMB file System, -o guest means using anounymous account
sudo mount -t cifs //192.168.0.103/Public /mnt/samba/ -o guest 
