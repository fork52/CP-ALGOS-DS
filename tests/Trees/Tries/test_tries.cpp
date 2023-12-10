#include "gtest/gtest.h"
#include "../../../Trees/Tries/tries.cpp"

TEST(TriesTests, SmallTest) {
    Trie trie;
    std::string app = "app", apple = "apple", applet = "applet", word = "abc";

    trie.insert(app); trie.insert(apple); trie.insert(applet);
    trie.insert(word);

    EXPECT_TRUE(trie.search(app));
    EXPECT_TRUE(trie.search(apple));
    EXPECT_TRUE(trie.search(applet));
    EXPECT_TRUE(trie.search(word));

    EXPECT_TRUE(trie.startsWith(app));
    EXPECT_TRUE(trie.startsWith(apple));
    EXPECT_TRUE(trie.startsWith(applet));
    EXPECT_TRUE(trie.startsWith(word));

    // Deleted Applet
    trie.deleteWord(applet);

    EXPECT_FALSE(trie.startsWith(applet));
    EXPECT_TRUE(trie.startsWith(app));
    EXPECT_TRUE(trie.startsWith(apple));
    EXPECT_TRUE(trie.startsWith(word));

    EXPECT_FALSE(trie.search(applet));
    EXPECT_TRUE(trie.search(apple));
    EXPECT_TRUE(trie.search(app));
    EXPECT_TRUE(trie.search(word));

    // Insert applet, remove apple
    trie.insert(applet); trie.deleteWord(apple);
    
    EXPECT_TRUE(trie.startsWith(apple));
    EXPECT_TRUE(trie.startsWith(app));
    EXPECT_TRUE(trie.startsWith(applet));
    EXPECT_TRUE(trie.startsWith(word));

    EXPECT_FALSE(trie.search(apple));
    EXPECT_TRUE(trie.search(applet));
    EXPECT_TRUE(trie.search(app));
    EXPECT_TRUE(trie.search(word));
}
