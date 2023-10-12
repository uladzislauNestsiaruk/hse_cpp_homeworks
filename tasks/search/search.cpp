#include "search.h"

#include <set>
#include <map>
#include <string>
#include <cmath>

void StringToLower(std::string& line) {
    for (size_t i = 0; i < line.size(); i++) {
        int32_t ascii_code = static_cast<int>(line[i]);
        line[i] = static_cast<char>((tolower(ascii_code)));
    }
}

void ClassifyIsWordInteresting(std::string& word, const std::set<std::string> interesting_words,
                               std::set<std::string>& appeared_interesting_words, int32_t& words_count) {
    StringToLower(word);
    if (interesting_words.find(word) != interesting_words.end()) {
        appeared_interesting_words.insert(word);
    }
    words_count += !word.empty();
    word.clear();
}

bool RecalculateIDFForString(const std::string_view& text, std::map<std::string, double>& idf,
                             const std::set<std::string>& interesting_words) {
    std::set<std::string> appeared_interesting_words;
    std::string word;
    int32_t words_count = 0;
    for (char character : text) {
        if (isalpha(character)) {
            word += character;
        } else {
            ClassifyIsWordInteresting(word, interesting_words, appeared_interesting_words, words_count);
        }
    }
    ClassifyIsWordInteresting(word, interesting_words, appeared_interesting_words, words_count);
    for (const std::string& interesting_word : appeared_interesting_words) {
        ++idf[interesting_word];
    }
    return words_count > 0;
}

void RecalculateLineWordAppearance(std::string& word, const std::set<std::string>& interesting_words,
                                   std::map<std::string, int32_t>& tf, double& words_count) {
    StringToLower(word);
    if (!word.empty()) {
        ++words_count;
        if (interesting_words.find(word) != interesting_words.end()) {
            ++tf[word];
        }
        word.clear();
    }
}

void ProcessLineTfIdf(const std::string_view& text, std::map<std::string, double>& idf,
                      const std::set<std::string>& interesting_words, std::vector<double>& tf_idf) {
    std::string word;
    std::map<std::string, int32_t> word_appearance;
    double words_count = 0;
    for (char character : text) {
        if (isalpha(character)) {
            word += character;
        } else {
            RecalculateLineWordAppearance(word, interesting_words, word_appearance, words_count);
        }
    }
    RecalculateLineWordAppearance(word, interesting_words, word_appearance, words_count);
    double tf_idf_line_value = 0;
    for (const std::string& interesting_word : interesting_words) {
        tf_idf_line_value += idf[interesting_word] * (word_appearance[interesting_word] / words_count);
    }
    tf_idf.emplace_back(tf_idf_line_value);
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    std::map<std::string, double> idf;
    std::set<std::string> interesting_words;
    std::vector<double> tf_idf;
    std::vector<int32_t> lines_relevance_index_order;
    std::vector<std::string_view> answer;
    std::vector<std::pair<int32_t, int32_t>> line_borders;
    std::string word;
    int32_t lines_in_text = 0;
    int32_t non_empty_lines = 0;
    for (char character : query) {
        if (isalpha(character)) {
            word += character;
        } else {
            if (!word.empty()) {
                StringToLower(word);
                interesting_words.insert(word);
            }
            word = "";
        }
    }
    if (!word.empty()) {
        StringToLower(word);
        interesting_words.insert(word);
    }
    word.clear();
    size_t left_pos = 0;
    while (left_pos < text.size()) {
        lines_relevance_index_order.emplace_back(lines_in_text);
        ++lines_in_text;
        size_t next_pos = text.find_first_of('\n', left_pos);
        if (next_pos == std::string::npos) {
            next_pos = text.size();
        }
        line_borders.push_back(std::make_pair(left_pos, next_pos));
        non_empty_lines += RecalculateIDFForString(text.substr(left_pos, next_pos - left_pos), idf, interesting_words);
        left_pos = next_pos + 1;
    }
    for (auto& word_idf : idf) {
        word_idf.second = log2(non_empty_lines / word_idf.second);
    }
    std::map<std::string, int32_t> current_tf;
    left_pos = 0;
    for (std::pair<int32_t, int32_t> borders : line_borders) {
        ProcessLineTfIdf(text.substr(borders.first, borders.second - borders.first), idf, interesting_words, tf_idf);
    }
    std::sort(lines_relevance_index_order.begin(), lines_relevance_index_order.end(),
              [tf_idf](int32_t left_index, int32_t right_index) { return tf_idf[left_index] > tf_idf[right_index]; });
    for (int32_t line_index : lines_relevance_index_order) {
        if (answer.size() == results_count) {
            break;
        }
        answer.push_back(text.substr(line_borders[line_index].first,
                                     line_borders[line_index].second - line_borders[line_index].first));
    }
    return answer;
}
