#include <iostream>
#include <utility>
#include <thread>
#include <future>
#include "words_lib.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;
using namespace testing;

TEST(WordsParser, should_parse_words_correctly) {
    WordsParser w(", ");
    w.parse("this, is, test,,, word");

    ASSERT_THAT(w.get_words(), ElementsAre("this", "is", "test,,", "word"));
}

class WordsParserStub : public IWordsParser
{
public:
    WordsParserStub(initializer_list<string> words) : m_words(words) {}

    void parse(const string& s) override
    {
        // do nothing
    }

    const vector<string>& get_words() const override { return m_words; }
private:
    vector<string> m_words;
};

TEST(WordCount, should_count_words_correctly) {
    WordsParserStub wp({"a", "b", "a", "def"});
    WordCount t(wp);
    t.process();
    EXPECT_EQ(t.get_count(), 3);
    EXPECT_EQ(t.get_count_of("a"), 2);
    EXPECT_EQ(t.get_count_of("invalid"), 0);
}

TEST(LongestWord, should_find_longest_correctly) {
    WordsParserStub wp({ "a", "b", "a", "def" });
    LongestWord t(wp);
    t.process();
    EXPECT_EQ(t.get_longest(), "def");
}

TEST(LongestRepeatableSequenceWord, should_find_longest_correctly) {
    WordsParserStub wp({ "aabaab", "aabaabaaba" });
    LongestRepeatableSequenceWord t(wp);
    t.process();
    EXPECT_EQ(t.get_sequence(), "aaba");
    EXPECT_EQ(t.get_word(), "aabaabaaba");
}

TEST(ReverseWordsOrder, should_reverse_correctly) {
    WordsParserStub wp({ "a", "b", "c"});
    ReverseWordsOrder t(wp);
    t.process();

    ASSERT_THAT(t.get_words(), ElementsAre("c", "b", "a"));
}

TEST(ReverseWordsOrder, should_sort_asc_correctly) {
    WordsParserStub wp({ "xxx", "apple", "abroad", "code", "coach", "beta" });
    Sort t(wp);
    t.process();

    ASSERT_THAT(t.get_words(), ElementsAre("abroad", "apple", "beta", "coach", "code", "xxx"));
}

TEST(ReverseWordsOrder, should_sort_desc_correctly) {
    WordsParserStub wp({ "xxx", "apple", "abroad", "code", "coach", "beta" });
    SortDesc t(wp);
    t.process();

    ASSERT_THAT(t.get_words(), ElementsAre("xxx", "code", "coach", "beta", "apple", "abroad"));
}

TEST(ReverseLetters, should_reverse_letters_correctly) {
    WordsParserStub wp({ "this", "is", "test" });
    ReverseLetters t(wp);
    t.process();

    ASSERT_THAT(t.get_words(), ElementsAre("siht", "si", "tset"));
}

TEST(Integration, should_execute_tasks_polymorphically) {
    WordsParser parser(" ");
    parser.parse("this is a test string waaaaaaaaay to simple simple simple");

    vector<shared_ptr<ITask>> tasks;
    tasks.push_back(make_shared<WordCount>(parser));
    tasks.push_back(make_shared<LongestWord>(parser));
    tasks.push_back(make_shared<LongestRepeatableSequenceWord>(parser));
    tasks.push_back(make_shared<ReverseWordsOrder>(parser));
    tasks.push_back(make_shared<Sort>(parser));
    tasks.push_back(make_shared<SortDesc>(parser));
    tasks.push_back(make_shared<ReverseLetters>(parser));

    vector<future<void>> futures;
    for (auto& t : tasks)
    {
        packaged_task<void(void)> foo([t]() { t->process(); });
        futures.push_back(foo.get_future());
        thread(move(foo)).detach();
    }

    for (auto& f : futures)
    {
        f.get();
    }

    for (const auto& t : tasks)
    {
        t->print(cout);
        cout << "--------------------------\n";
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}