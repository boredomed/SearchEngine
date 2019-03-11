# SearchEngine
A search engine in c++ on wikipedia data using pugi xml parser.
### Setup
Create a c++ project in Visual Studio or any of your choice add teh souce code, liberaries and wikipedia data and you are good to go.

## Dependencies
Pugi xml</br>
Wikipedia dump data</br>

## Description
Parse the query.</br>
Convert words into wordIDs</br>
Tokenizing the text data</br>
Seek to the start of the doclist in the short barrel for every word.</br>
Scan through the doclists until there is a document that matches all the search terms.</br>
Compute the rank of that document for the query.</br>
Sort the documents that have matched by rank and return the top k.</br>

## Specifications 
Creating document object loading xml file and creating a tree</br>
Tokenizing the text data</br>
Forward Indexing (ist of terms contained within a particular document) and Inverted Indexing (list of documents containing a given term)</br>
Processing the queery</br>
Traversing the pages ie crawling</br>
Single word, multiword search queeries</br>

