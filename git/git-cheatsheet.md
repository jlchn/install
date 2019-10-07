### 1.Undo a commit
Say you have this, where C is your HEAD and (F) is the state of your files.
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(F)  
A-B-C  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;↑  
  master  

you want to nuke commit C and never see it again. You do this:
```java
git reset --hard HEAD~1
```
The result is:
>&nbsp;&nbsp;&nbsp;(F)  
 A-B  
&nbsp;&nbsp;&nbsp;↑  
 master  

Now B is the HEAD. Because you used --hard, your files are reset to their state at commit B.

What if you want to undo the commit but keep your changes for a bit of editing before you do a better commit.this time just leave off the --hard:
```bash
git reset HEAD~1
```
In this case the result is:
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; (F)  
A-B-C  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;↑  
master  

For the lightest touch, you can even undo your commit but leave your files and your index:
```
git reset --soft HEAD~1
```
This not only leaves your files alone, it even leaves your index alone. When you do git status, you'll see that the same files are in the index as before. In fact, right after this command, you could do git commit and you'd be redoing the same commit you just had.

### 2.rebase and stash
when run with `git pull --rebase`, sometimes we may get following error:
>Cannot pull with rebase: You have unstaged changes.

If you don't want to keep the changes you can do `git checkout -- <file name>` or `git reset --hard` to get rid of the changes.

If you want to keep the changes, you can run `git stash`, it stores the differences away from everything else, returning your working directory to the last commit. Once you have done your rebase, run `git stash pop`. This will return those files to the working directory and allow you to work as before.

