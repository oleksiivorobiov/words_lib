#include "words_lib.h"

using namespace std;

void WordsParser::parse(const string& s)
{
    const size_t delim_len = m_delim.length();
    size_t pos_start = 0, pos_end;

    while ((pos_end = s.find(m_delim, pos_start)) != string::npos) {
        string word = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        m_words.push_back(move(word));
    }

    m_words.push_back(s.substr(pos_start));
}

void WordCount::process()
{
    for (const auto &w : m_parser.get_words())
    {
        ++m_occurrences[w];
    }
}

void WordCount::print(ostream &out) const
{
    out << "Count of words: " << m_occurrences.size() << "\n";
    for (const auto& p : m_occurrences)
    {
        out << p.first << "\t-\t" << p.second << " occurrences\n";
    }
}

void LongestWord::process()
{
    const auto &words = m_parser.get_words();
    auto longest_it = words.cbegin();
    for (auto it = words.cbegin() + 1; it != words.cend(); ++it)
    {
        if (it->size() > longest_it->size())
            longest_it = it;
    }

    m_res = *longest_it;
}

void LongestWord::print(ostream& out) const
{
    out << "Longest word: " << m_res << "\n";
}

void LongestRepeatableSequenceWord::process()
{
    for (const auto& w : m_parser.get_words())
    {
        string lrs = longest_repeated_substring(w);
        if (lrs.size() > m_sequence.size())
        {
            m_sequence = move(lrs);
            m_word = w;
        }
    }
}

void LongestRepeatableSequenceWord::print(ostream& out) const
{
    out << "Word with longest repeatable sequence: " << m_word << "(" << m_sequence << ")" << "\n";
}

string LongestRepeatableSequenceWord::longest_repeated_substring(const string &str)
{
    // Dynamic Programming O(n^2) solution from
    // https://www.geeksforgeeks.org/longest-repeating-and-non-overlapping-substring/
    const size_t n = str.length();
    vector<vector<size_t>> LCSRe;
    LCSRe.resize(n + 1);
    for (auto &v : LCSRe)
    {
        v.resize(n + 1);
    }

    string res; // To store result
    size_t res_length = 0; // To store length of result

    // building table in bottom-up manner
    size_t i, index = 0;
    for (i = 1; i <= n; i++)
    {
        for (size_t j = i + 1; j <= n; j++)
        {
            // (j-i) > LCSRe[i-1][j-1] to remove
            // overlapping
            if (str[i - 1] == str[j - 1] &&
                LCSRe[i - 1][j - 1] < (j - i))
            {
                LCSRe[i][j] = LCSRe[i - 1][j - 1] + 1;

                // updating maximum length of the
                // substring and updating the finishing
                // index of the suffix
                if (LCSRe[i][j] > res_length)
                {
                    res_length = LCSRe[i][j];
                    index = max(i, index);
                }
            }
            else
                LCSRe[i][j] = 0;
        }
    }

    // If we have non-empty result, then insert all
    // characters from first character to last
    // character of string
    if (res_length > 0)
        for (i = index - res_length + 1; i <= index; i++)
            res.push_back(str[i - 1]);

    return res;
}

void ReverseWordsOrder::process()
{
    const auto& words = m_parser.get_words();
    m_reversed_words.reserve(words.size());
    for (auto it = words.rbegin(); it != words.rend(); ++it)
    {
        m_reversed_words.push_back(*it);
    }
}

void ReverseWordsOrder::print(ostream& out) const
{
    out << "Words in reversed order: ";
    for (const auto& w : m_reversed_words)
    {
        out << w << " ";
    }
}

void Sort::process()
{
    m_sorted_words = m_parser.get_words();
    const size_t size = m_sorted_words.size();
    // bubble sort to fit the requirement not to use existing std func to do the whole work
    for (size_t i = 0; i < size - 1; i++)
    {
        for (size_t j = 0; j < size - i - 1; j++)
        {
            if (comparator(m_sorted_words[j], m_sorted_words[j + 1]))
            {
                swap(m_sorted_words[j], m_sorted_words[j + 1]);
            }
        }
    }
}

void Sort::print(ostream& out) const
{
    out << "Sorded words(asc): ";
    for (const auto& w : m_sorted_words)
    {
        out << w << " ";
    }
}

void SortDesc::print(std::ostream& out) const
{
    out << "Sorded words(desc): ";
    for (const auto& w : get_words())
    {
        out << w << " ";
    }
}

void ReverseLetters::process()
{
    const auto& words = m_parser.get_words();
    m_words.reserve(words.size());
    for (const auto& w : words)
    {
        string reversed_w;
        reversed_w.reserve(w.size());
        for (auto it = w.rbegin(); it != w.rend(); ++it)
        {
            reversed_w.push_back(*it);
        }
        m_words.push_back(move(reversed_w));
    }
}

void ReverseLetters::print(ostream& out) const
{
    out << "Reversed letters: ";
    for (const auto& w : m_words)
    {
        out << w << " ";
    }
}