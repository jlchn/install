
### Connect to github

```
cd ~/.ssh
ssh-keygen -t rsa -C "xxx@xxx.com"
ssh-keyscan -t rsa github.com > ~/.ssh/known_hosts
#add public key to github and then test with:
ssh -T git@github.com
```

### Set multiple repositories

First, create two pairs of ssh keys in ~/.ssh forlder.
Second, create a condig file in ~/.ssh folder.

```
cd ~/.ssh
touch config
```

Then, past below to config file

```
#GITLAB  
Host gitlab.company_url.com  
HostName gitlab.company_url.com  
PreferredAuthentications publickey  
IdentityFile ~/.ssh/id_rsa_company  
#GITHUB
Host github.com
HostName github.com
PreferredAuthentications publickey
IdentityFile ~/.ssh/id_rsa_home
```