#include "bitset.h"
#include <math.h>

// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size) {
    struct bitset * set=malloc(sizeof(struct bitset));
    //struct bitset * result;
    float word_size= sizeof(uint64_t)*8;
    int words= ceil(size/word_size);
    set->size_in_words= words;
    set->universe_size= size;
    set->bits= malloc(sizeof(uint64_t)*words);

    for(int i =0 ; i<words; i++)
    {
        set->bits[i]=0;
    }
    return set;
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset * this) {

    return this->universe_size;
}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset *this)
{
    int items_stored=0;
    for(int i=0; i<this->size_in_words; i++)
    {
        int word_size= sizeof(uint64_t)*8;
        int bit = i % word_size;
        uint64_t word = this->bits[i];
        uint64_t mask = 1ULL<<bit;
        while(word!=0)
        {
            uint64_t is_word= mask & word;
            if(is_word!=0)
            {
                items_stored++;
            }
            word=word>>1;
        }
    }
    return items_stored;
}

// check to see if an item is in the set
int bitset_lookup(struct bitset * this, int item){
    int word_size= sizeof(uint64_t)*8;
    int word = item/ word_size;
    int bit = item % word_size;
    uint64_t lookup = this->bits[word];
    uint64_t mask = 1ULL<<bit;
    lookup= mask &lookup;
    //have a doubt over here
    if(lookup!=0)
    {
        return 1;
    }
    return 0;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset * this, int item) {
	int word_size= sizeof(uint64_t)*8;
    int word = item/ word_size;
    int bit = item % word_size;
    uint64_t old_value= this->bits[word];
    uint64_t mask = 1ULL<<bit;
    this->bits[word]= old_value|mask;
}

// remove an item with number 'item' from the set
void bitset_remove(struct bitset * this, int item) {
	int word_size= sizeof(uint64_t)*8;
    int word = item/ word_size;
    int bit = item % word_size;
    uint64_t old_value= this->bits[word];
    uint64_t mask = 1ULL<<bit;
    old_value= old_value|mask;
    this->bits[word]= old_value^mask;
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {
        if((bitset_size(dest)==bitset_size(src1))&&(bitset_size(dest)==bitset_size(src2)))
        {
            for (int i=0; i<src1->size_in_words; i++)
            {
             dest->bits[i]= src1->bits[i]|src2->bits[i];
            }
        }
        //else{}
}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {
       if((bitset_size(dest)==bitset_size(src1))&&(bitset_size(dest)==bitset_size(src2)))
        {
            for (int i=0; i<src1->size_in_words; i++)
            {
             dest->bits[i]= src1->bits[i]&src2->bits[i];
            }
        }
       // else{}
}
