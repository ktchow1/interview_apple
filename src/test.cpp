#include<iostream>
#include<trie.h>

void test_siri(const std::string& s, const std::set<Siri::Concept>& ans)
{
    Siri::Trie trie;
    trie.add_concept("hello world");
    trie.add_concept("class ");
    trie.add_concept("based class");
    trie.add_concept("derived class");
    trie.add_concept("algorithm optimization");
    trie.add_concept("binary search algorithm");
    trie.add_concept("binary tree");
    trie.add_concept("tree algorithm");
    trie.add_concept("graph search");
    trie.add_concept("graph object");
    trie.add_concept("object");

    auto out = trie.extract_concept(s);

    bool correct = true;
    auto iter0 = ans.begin();
    auto iter1 = out.begin();
    while(iter0 != ans.end() && iter1 != out.end())
    {
        if (*iter0 != *iter1) 
        {
            correct = false;
            break;
        }
        ++iter0;
        ++iter1;
    }
    if (iter0 != ans.end()) correct = false;
    if (iter1 != out.end()) correct = false;

    if (correct)
    {
        std::cout << "\ncorrect";
    }
    else
    {
        std::cout << "\nincorrect";
        std::cout << "\nexpect : ";
        for(const auto& x:ans) std::cout << x << " ";
        std::cout << "\noutput : ";
        for(const auto& x:out) std::cout << x << " ";
    }
}

int main()
{
    std::string s;
    std::set<Siri::Concept> ans;
    

    s = "### ABCDF $$$HeLLO world #ABC# hello classA WORLD class$%^"; 
    ans = 
    { 
        Siri::Concept("hello world"),
        Siri::Concept("class")
    };
    test_siri(s, ans);
    

    s = "###$$$HeLLO world #ABC# hEllo CLassA GRaph imaGe cAChe GRaph*ObjECT"; 
    ans = 
    {   
        Siri::Concept("hello world"),
        Siri::Concept("graph object"),
        Siri::Concept("object")
    };
    test_siri(s, ans);


    s = "###$$$HeLLO base deriVEd class #ABC# cache quanTLib gRAph A OBject"; 
    ans = 
    {   
        Siri::Concept("derived class"),
        Siri::Concept("class"),
        Siri::Concept("object")
    };
    test_siri(s, ans);


    s = "###$$$algorIThm tREe GRaph trEe sEArch alGOriThm biNAry sEArch tree 223"; 
    ans = 
    {   
    };
    test_siri(s, ans);


    s = "###$ binary sEArch alGoRIthm opTImiZAtion cONtainer binAry TRee algORithm grAPh oBJect 223"; 
    ans = 
    {   
        Siri::Concept("binary search algorithm"),
        Siri::Concept("algorithm optimization"),
        Siri::Concept("binary tree"),
        Siri::Concept("tree algorithm"),
        Siri::Concept("graph object"),
        Siri::Concept("object")
    };
    test_siri(s, ans);


    std::cout << "\n\n\n";
    return 0;
}

