# Please use gcc10 to compile the project (use std c++20), follow the steps :
1. mkdir build
2. cd build
3. mkdir debug
4. cd debug
5. cmake -DCMAKE_BUILD_TYPE=Debug ../..
6. make 
7. ./Test 

# Concept can be multi-word, we need two layers of search
1. low-level search for word, using either std::map or std::unordered_map
2. high-level search for concept, using trie

# Remarks :
1. std::map is a binary tree taking O(log2(N)) search time
2. std::unordered_map is a hashmap taking O(1) search time for no collision, O(N) otherwise
3. in a balanced binary tree with one million (~2^20) leaves, 20 decisions are needed to traverse from the root to a leaf
4. finally, I pick std::unordered_map for the low-level search



