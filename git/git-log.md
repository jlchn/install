
```bash
git log 
git log abc.php # list the commit history of abc.php
git log --follow abc.php # list the commit history of abc.php following with the history before renaming
git log master
git log master~5..master~3 #since..until，specify the 3th and 2ed prior commits on the master branch
```

_result_

>commit ec232cddfb94e0dfd5b5855af8ded7f5eb5c90d6  
Author: Jiang <sample@example.com>  
Date: Wed Apr 2 16:47:42 2008 -0500  
Convert to HTML  
commit 9da581d910c9c4ac93557ca4859e767f5caf5169  
Author: Jiang <sample@example.com>  
Date: Thu Mar 13 22:38:13 2008 -0500  
Initial contents of public_html  
see commit detail  

```bash
git show ec232c #show with commit number
```

_result_

>commit 9da581d910c9c4ac93557ca4859e767f5caf5169  
Author: Jiang <sample@example.com>  
Date: Thu Mar 13 22:38:13 2008 -0500  
Initial contents of public_html  
diff --git a/index.html b/index.html  
new file mode 100644  
index 0000000..34217e9  
--- /dev/null  
+++ b/index.html  
@@ -0,0 +1 @@  
+My web site is alive!  
