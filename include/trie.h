#include<string>
#include<vector>
#include<set>
#include<unordered_map>
#include<algorithm>

namespace Siri {
std::vector<std::string> word_segmentation(const std::string& s)
{
    std::string input = s;
    std::vector<std::string> output;
    std::for_each(input.begin(), input.end(), [](char& c) { c = std::tolower(c); });

    size_t pos = 0;
    while(pos < input.size())
    {
        auto pos_begin = input.find_first_of("abcdefghijklmnopqrstuvwxyz", pos);
        if (pos_begin != std::string::npos)
        {
            auto pos_end = input.find_first_not_of("abcdefghijklmnopqrstuvwxyz", pos_begin);
            if (pos_end != std::string::npos)
            {
                output.push_back(input.substr(pos_begin, pos_end-pos_begin));
                pos = pos_end;
            }
            else
            {
                output.push_back(input.substr(pos_begin));
                pos = input.size();
            }
        }
        else pos = input.size();
    }
    return output;
}

// *************** // 
// *** Concept *** //
// *************** // 
class Trie;              // Forward declaration
class Concept            // Concept is a vector of words.
{
public:
    Concept() = default;
   ~Concept() = default;
    Concept(const Concept&) = default;
    Concept(Concept&&) = default;
    Concept& operator=(const Concept&) = default;
    Concept& operator=(Concept&&) = default;

public:
    explicit Concept(const std::string& s) : _impl{word_segmentation(s)}
    {
    }

    auto operator<=>(const Concept& rhs) const noexcept 
    {
        auto iter0 = _impl.begin();
        auto iter1 = rhs._impl.begin();
        while(iter0 != _impl.end() && iter1 != rhs._impl.end())
        {
            if      (*iter0 > *iter1) return std::strong_ordering::greater;
            else if (*iter0 < *iter1) return std::strong_ordering::less;
            ++iter0;
            ++iter1;
        }
        if (iter0 != _impl.end())     return std::strong_ordering::greater;
        if (iter1 != rhs._impl.end()) return std::strong_ordering::less;
        return std::strong_ordering::equal;
    }

    bool operator==(const Concept& rhs) const noexcept 
    {
        return (*this<=>rhs) == std::strong_ordering::equal;
    }

private:
    friend class Trie;
    friend std::ostream& operator<<(std::ostream&, const Siri::Concept&);

private:
    std::vector<std::string> _impl;
};

// Dash is added to join words in the same concept for readability
inline std::ostream& operator<<(std::ostream& os, const Siri::Concept& c)
{
    for(const auto& word : c._impl)
    {
        os << word << "_";
    }
    return os;
}

// ********************* // 
// *** Node and Trie *** //
// ********************* // 
class node
{
public:
    node() : _children{}, _eoc(false) 
    {
    }

private:
    friend class Trie;

private:
    std::unordered_map<std::string, node*> _children;
    bool _eoc; // end of concept
};

class Trie
{
public:
    Trie() = default;
   ~Trie() = default;
    Trie(const Trie&) = default;
    Trie(Trie&&) = default;
    Trie& operator=(const Trie&) = default;
    Trie& operator=(Trie&&) = default;

public:
    void add_concept(const std::string& s)
    {
        Concept c(s);

        node* node_ptr = &_root;
        for(const auto& word : c._impl)
        {
            auto iter = node_ptr->_children.find(word);
            if (iter != node_ptr->_children.end())
            {
                node_ptr = iter->second;
            }
            else
            {
                auto [map_iter, flag] = node_ptr->_children.insert(std::make_pair(word, new node{}));
                node_ptr = map_iter->second;
            }
        }
        node_ptr->_eoc = true;
    }

    std::set<Concept> extract_concept(const std::string& s) const
    {
        auto words = word_segmentation(s);

        std::set<Concept> output;
        for(auto word_iter = words.begin(); word_iter!=words.end(); ++word_iter)
        {
            Concept c;

            auto node_ptr = &_root;
            auto word_iter0 = word_iter;
            while(node_ptr != nullptr && word_iter0 != words.end())
            {
                node_ptr = find(node_ptr, *word_iter0);
                if (node_ptr)
                {
                    c._impl.push_back(*word_iter0);
                    if (node_ptr->_eoc)
                    {
                        output.insert(c);
                    }
                    ++word_iter0;
                }
            }
        }

        return output; // return by value is fine (due to NRVO / copy-epsilon)
    }

private:
    const node* find(const node* node_ptr, const std::string& word) const noexcept
    {
        auto iter = node_ptr->_children.find(word);
        if (iter != node_ptr->_children.end())
        {
            return iter->second;
        }
        return nullptr;
    }

private:
    node _root;
};
}

