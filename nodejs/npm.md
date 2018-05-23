```bash
npm search db # locate the modules by keywords db
npm install commander@">1.0.0" # greater than version 1.0.0
npm install commander@1.0.0 # exactly matches version 1.0.0
npm install commander@"=1.0.0" # exactly matches version 1.0.0
npm install commander@"~1.0.0" # greater than or equal to version 1.0.0 , but less than the mexe major version

npm outdated [module-name] [-g] # display outdated packages [in golbal folder]
npm update [module-name] [-g]  # update outdated packages [in golbal folder]

npm adduser
npm publish

npm ls # view all the m-odules installed in current directory
npm ls -g # view all the modules installed in global directory
npm root -g # view the path that the global modules been installed

npm rm module-name # remove a module

# linking packages is very useful if you are developing a module and want another project to reference your local copy of the module . 
# a linked package can be refered as if it were a global package , 
# which is very similar to module installation . 
#1. create global link
cd my-project & npm link # now your 'my-project' is a global module , you can verify using npm ls -g 
#2. reference an existing link 
cd other-project & npm link my-project # link my-project as a module in your other-project 
#3.unlink package 
cd other-project & npm unlink my-project 
cd my-project & npm unlink 

```
