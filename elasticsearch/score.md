# TF, DF, IDF

- TF 
  - term frequency
  - how frequent does the searched term appear in one document
  - if there are 10 words in a document, and `elastic` appears 3 times, the TF if 0.3
 
- DF
  - document frequency
  - the total number of documents which are containing the searched term
  - if there are 10 documents in an index, and the searched term `elastic` appears in 5 documents, DF is 5.
  
- IDF
  - IDF = log(total document number/(DF + 1))
  - when a term appears in all documents, IDF is nearly to 1
  - `+ 1` is to avoid zero divider.
  
  let's say there are 10 documents
  the term `elastic` appears 3,4,5 times respectively in these 3 documents. the DF is 3,
  ```
  doc   1     2     3 
  TF    0.3   0.4   0.5
 
  ```
so TF * IDF for each documents are:  0.3 * log(10 / (3 + 1)), 0.4 * log(10 / (4 + 1)), 0.5 * log(10 / (5 + 1))

TF * IDF is the final score for each documents for this search.

# BM25

# How to score while searching multiple fields
