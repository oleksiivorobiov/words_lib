#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class IWordsParser
{
public:
    virtual void parse(const std::string& s) = 0;
    virtual const std::vector<std::string>& get_words() const = 0;
    virtual ~IWordsParser() = default;
};

class WordsParser : public IWordsParser
{
public:
    WordsParser(const std::string& delim) : m_delim(delim) {}
    void parse(const std::string& s) override;
    const std::vector<std::string>& get_words() const override { return m_words; }
private:
    const std::string m_delim;
    std::vector<std::string> m_words;
};

class ITask
{
public:
    virtual void process() = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual ~ITask() = default;
};

class WordCount : public ITask
{
public:
    WordCount(IWordsParser& p) : m_parser(p) {}
    void process() override;
    void print(std::ostream& out) const override;
    size_t get_count() const { return m_occurrences.size(); }
    size_t get_count_of(const std::string &s) const { return m_occurrences.count(s) ? m_occurrences.at(s) : 0; }
private:
    IWordsParser& m_parser;
    std::unordered_map<std::string, size_t> m_occurrences;
};

class LongestWord: public ITask
{
public:
    LongestWord(IWordsParser& p) : m_parser(p) {}
    void process() override;
    void print(std::ostream& out) const override;
    std::string get_longest() const { return m_res; }
private:
    IWordsParser& m_parser;
    std::string m_res;
};

class LongestRepeatableSequenceWord : public ITask
{
public:
    LongestRepeatableSequenceWord(IWordsParser& p) : m_parser(p) {}
    void process() override;
    void print(std::ostream& out) const override;
    std::string get_sequence() const { return m_sequence; }
    std::string get_word() const { return m_word; }
private:
    IWordsParser& m_parser;
    std::string m_sequence, m_word;

    std::string longest_repeated_substring(const std::string& str);
};

class ReverseWordsOrder : public ITask
{
public:
    ReverseWordsOrder(IWordsParser& p) : m_parser(p) {}
    void process() override;
    void print(std::ostream& out) const override;
    std::vector<std::string> get_words() const { return m_reversed_words; }
private:
    IWordsParser& m_parser;
    std::vector<std::string> m_reversed_words;
};

class Sort : public ITask
{
public:
    Sort(IWordsParser& p) : m_parser(p) {}
    void process() override;
    void print(std::ostream& out) const override;
    std::vector<std::string> get_words() const { return m_sorted_words; }
private:
    IWordsParser& m_parser;
    std::vector<std::string> m_sorted_words;

    virtual bool comparator(const std::string& s1, const std::string& s2) const { return s1 > s2; }
};

class SortDesc : public Sort
{
public:
    SortDesc(IWordsParser& p) : Sort(p) {}
    void print(std::ostream& out) const override;
private:
    bool comparator(const std::string& s1, const std::string& s2) const override { return s1 < s2; }
};

class ReverseLetters : public ITask
{
public:
    ReverseLetters(IWordsParser& p) : m_parser(p) {}
    void process() override;
    void print(std::ostream& out) const override;
    std::vector<std::string> get_words() const { return m_words; }
private:
    IWordsParser& m_parser;
    std::vector<std::string> m_words;
};