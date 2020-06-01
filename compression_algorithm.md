The compression algorithm implemented in ProcessController::compress is the simple dictionary compression 
mentioned in README.md. 

It simply creates a dictionary based on the input file, generated only using words 
that have frequency above 1 (non-unique words). It then replaces each instance of this word (with punctuation
intact) with an equivalent integer representation for that word, or its 'key'. While this may be inefficient for larger 
text files, for the purposes of files less than a certain amount of words it works decently well. This 
dictionary is stored within the ProcessController as the dict member, which is a vector of dict_pair structs,
each of which includes a word and its associated key. (Note: This relation was not stored as a map since 
the STL implementation of maps is not bidirectional, which is necessary for decompression)

For decompression, these keys in the string are then replaced again with the associated 
key and given back to the output stream.