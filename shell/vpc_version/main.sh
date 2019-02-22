
bash fetch_current.sh
bash diff.sh
bash post.sh && cp previous previous.bak.$(date +%Y%m%d%H%M%S) && rm previous && cp current previous && echo "post success" || echo "post has errors"
