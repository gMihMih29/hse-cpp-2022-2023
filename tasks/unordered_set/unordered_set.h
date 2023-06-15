#pragma once

#include <functional>
#include <iterator>
#include <list>
#include <utility>
#include <vector>

template <typename KeyT>
class UnorderedSet {
public:
    UnorderedSet() : n_elements_(0) {
    }

    explicit UnorderedSet(size_t count) : UnorderedSet() {
        Reserve(2 * count);
    }

    template <typename IteratorType,
              typename = std::enable_if_t<std::is_base_of_v<
                  std::forward_iterator_tag, typename std::iterator_traits<IteratorType>::iterator_category>>>
    UnorderedSet(IteratorType first, IteratorType last) : UnorderedSet(std::distance(first, last)) {
        while (first != last) {
            data_[std::hash(*first)].push_back(*first);
            ++first;
        }
    }

    UnorderedSet(const UnorderedSet& other) {
        n_elements_ = other.Size();
        Reserve(other.Bucket());
        for (size_t i = 0; i < other.Bucket(); ++i) {
            data_[i] = other.data_[i];
        }
    }

    UnorderedSet(UnorderedSet&& other) {
        n_elements_ = std::move(other.n_elements_);
        data_ = std::move(other.data_);
    }

    ~UnorderedSet() = default;

    UnorderedSet& operator=(const UnorderedSet& other) {
        UnorderedSet tmp(other);
        Swap(tmp);
        return *this;
    }

    UnorderedSet& operator=(UnorderedSet&& other) {
        Swap(other);
        return *this;
    }

    size_t Size() const {
        return n_elements_;
    }

    bool Empty() const {
        return n_elements_ == 0;
    }

    void Clear() {
        UnorderedSet tmp();
        Swap(tmp);
    }

    void Insert(const KeyT& key) {
        if (n_elements_ == data_.size()) {
            Reserve(2 * n_elements_);
        }
        ++n_elements_;
        data_[std::hash(key) % data_.size()].push_back(key);
    }

    void Insert(KeyT&& key) {
        if (n_elements_ == data_.size()) {
            Reserve(2 * n_elements_);
        }
        ++n_elements_;
        data_[std::hash(key) % data_.size()].emplace_back(key);
    }

    void Erase(const KeyT& key) {
        data_[std::hash(key) % data_.size()].clear();
    }

    bool Find(const KeyT& key) const {
        return !data_[std::hash(key) % data_.size()].empty();
    }

    void Rehash(size_t new_bucket_count) {
        if (data_.size() >= new_bucket_count) {
            return;
        }
        std::vector<std::list<KeyT>> tmp(new_bucket_count);
        for (const KeyT& elem : data_) {
            tmp[std::hash(elem) % new_bucket_count] = elem;
        }
        data_ = std::move(tmp);
    }

    void Reserve(size_t new_bucket_count) {
        if (data_.size() >= new_bucket_count) {
            return;
        }
        std::vector<std::list<KeyT>> tmp(new_bucket_count);
        for (size_t i = 0; i < data_.size(); ++i) {
            tmp[i] = data_[i];
        }
        data_ = std::move(tmp);
    }

    size_t BucketCount() const {
        return data_.size();
    }

    size_t BucketSize(size_t id) const {
        return data_[i].size();
    }

    size_t Bucket(const KeyT& key) const {
        return std::hash(key) % data_.size();
    }

    double LoadFactor() const {
        return static_cast<double>(n_elements_) / data_.size();
    }

    void Swap(UnorderedSet& other) {
        std::vector<std::list<KeyT>> tmp = std::move(other.data_);
        other.data_ = std::move(first);
        data_ = std::move(tmp);
        std::swap(n_elements_, other.n_elements_);
    }

private:
    size_t n_elements_;
    std::vector<std::list<KeyT>> data_;
};
