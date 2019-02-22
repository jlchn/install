An inode is a data structure on a filesystem on Linux and other Unix-like operating systems that stores all the information about a file except its name and its actual data.

When a file is created, it is assigned both a name and an inode number, which is an integer that is unique within the filesystem. Both the file names and their corresponding inode numbers are stored as entries in the directory that appears to the user to contain the files. That is, the directory associates file names with inodes.

Whenever a user or a program refers to a file by name, the operating system uses that name to look up the corresponding inode, which then enables the system to obtain the information it needs about the file to perform further operations. 

When a new hard link to a file is created, both links share the same inode number because the link is only a pointer, not a copy of the file.

There are two ways in which a filesystem can run out of space: it can consume all the space for adding new data (i.e., to existing files or to new files), or it can use up all the inodes

It is particularly easy to run out of inodes if a filesystem contains a very large number of very small files. 
