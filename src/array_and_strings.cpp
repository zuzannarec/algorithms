#include "array_and_strings.h"

bool check_if_unique(std::string str)
{
    uint32_t size = str.size();
    char checked[size];
    for (uint32_t i = 0; i < size; i++)
    {
        for (uint32_t j = 0; j < i; j++)
        {
            if (str.at(i) == checked[j])
            {
                return false;
            }
        }
        checked[i] = str.at(i);
    }
    return true;
}

bool is_permutation(std::string str, std::string to_check)
{
    if (str.size() != to_check.size())
    {
        return false;
    }
    return is_permutation_(str, to_check);
}

bool is_permutation_(std::string str, std::string to_check)
{
    if (to_check == "")
    {
        return true;
    }
    for (uint32_t i = 0; i < str.size(); i++)
    {
        if (str[i] == to_check[0])
        {
            to_check.erase(to_check.begin());
            str = str.substr(0, i) + str.substr(i + 1, str.size() - i - 1);
            if (!is_permutation_(str, to_check))
            {
                return false;
            }
            return true;
        }
    }
    return false;
}

bool is_permutation_count_method(std::string str1, std::string str2)
{
    if (str1.length() != str2.length())
    {
        return false;
    }
    int count[256] = {0};
    for (uint i = 0; i < str1.length(); i++)
    {
        int val = str1[i];
        count[val]++;
    }
    for (uint j = 0; j < str2.length(); j++)
    {
        int val = str2[j];
        count[val]--;
        if (count[val] < 0)
        {
            return false;
        }
    }
    return true;
}

void urlify(char* str, int len)
{   int token_len = 3;
    const char token[token_len] = "%20";
    char* tmp = str + len - 1;
    int inserted = 0;
    for (int i = 0; i < len; i++)
    {
        if (*tmp == ' ')
        {
            char* tmp1 = str + len + token_len - 2 + inserted;
            char* tmp2 = str + len - 1 + inserted;
            for (int j = 0; j < i + inserted; j++)
            {
                *tmp1 = *tmp2;
                tmp1--;
                tmp2--;
            }
            for (int k = token_len - 1; k >= 0; k--)
            {
                *tmp1 = token[k];
                tmp1--;
            }
            inserted += 2;
        }
        tmp--;
    }
}

void urlify_count_method(char* str, int len)
{
    int token_len = 3;
    int spaces = 0;
    for (int i = 0; i < len; i++)
    {
        if (str[i] == ' ')
        {
            spaces++;
        }
    }

    int additional = spaces * (token_len - 1);
    int expected_len = len + additional;
    char* tmp1 = str + expected_len - 1;
    char* tmp2 = str + len - 1;
    for (int j = 0; j < len; j++)
    {
        if (*tmp2 == ' ')
        {
            *tmp1 = '0';
            tmp1--;
            *tmp1 = '2';
            tmp1--;
            *tmp1 = '%';
        }
        else
        {
            *tmp1 = *tmp2;
        }
        tmp1--;
        tmp2--;
    }
}

bool is_palidrom_permutation(std::string str)
{
    std::vector<char> unique;
    unique.reserve(str.length());
    std::vector<uint> space_idx;
    space_idx.reserve(str.length());
    char val_single = ' ';
    int single = 0;
    int chars_count = 0;
    int chars[256] = {0};
    for (auto& ch : str)
    {
        if (ch != ' ')
        {
            int val = std::tolower(ch);
            chars[val]++;
            chars_count++;
        }
    }
    // even length
    if (chars_count % 2 == 0)
    {
        for (uint i = 0; i < str.length(); i++)
        {
            if (str[i] == ' ')
            {
                space_idx.push_back(i);
                continue;
            }
            int val = std::tolower(str[i]);
            if (chars[val] == 0)
            {
                continue;
            }
            if (chars[val] % 2 != 0)
            {
                return false;
            }
            unique.push_back(std::tolower(str[i]));
            chars[val] -= 2;
        }
    }
    // odd length
    else
    {
        for (uint i = 0; i < str.length(); i++)
        {
            if (str[i] == ' ')
            {
                space_idx.push_back(i);
                continue;
            }
            int val = std::tolower(str[i]);
            if (chars[val] == 0)
            {
                continue;
            }
            if (chars[val] % 2 != 0)
            {
                if (single == 0)
                {
                    single++;
                    val_single = std::tolower(str[i]);
                    continue;
                }
                else
                {
                    return false;
                }
            }
            unique.push_back(std::tolower(str[i]));
            chars[val] -= 2;
       }      
    }
    std::cout << "Permutations: " << std::endl;
    palindrom_permutations(unique, space_idx, val_single);
    return true;
}

void palindrom_permutations(std::vector<char> unique, std::vector<uint> space_idx, char single)
{
    palindrom_permutations_(unique, space_idx, single, "");
}

void palindrom_permutations_(std::vector<char> unique, std::vector<uint> space_idx, char single, std::string out)
{
    if (unique.size() == 0)
    {
        uint length_tmp = out.length();
        if (single != ' ')
        {
            out += single;
        }
        for (int i = length_tmp - 1; i >= 0; i--)
        {
            out += out[i];
        }
        for (int j = out.length() - 1; j > 0; j--)
        {
            for (auto& idx : space_idx)
            {
                if (static_cast<int>(idx) == j)
                {
                    auto out1 = out.substr(0, j);
                    auto out2 = out.substr(j, out.length() - j);
                    out = out1 + ' ' + out2;
                }
            }
        }
        std::cout << out << std::endl;
    }
    for (uint i = 0; i < unique.size(); i++)
    {
        auto foo = out + unique[i];
        std::vector<char> unique_reduced;
        for (uint j = 0; j < unique.size(); j++)
        {
            if (j != i)
            {
                unique_reduced.push_back(unique[j]);
            }
        }
        palindrom_permutations_(unique_reduced, space_idx, single, foo);
    }
}