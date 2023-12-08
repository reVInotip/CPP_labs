#include <vector>
#include <unordered_set>

using std::vector, std::unordered_set;

class Field {
    private:
        vector<char> field_;
        long long width_;
        long long height_;

        void CalcBitsPosition(long long (&bits)[9], long long j) const;
        void CalcBytesPosition(long long (&pos)[9], long long j) const;
    public:
        Field();
        Field(const vector<char>& field, const long long width, const long long height);
        ~Field() = default;
        long long GetWidth() const;
        long long GetHeight() const;
        vector<char> GetField() const;
        bool IsLife(long long x, long long y) const;
        void SetField(const int countIterations, unordered_set<char>& birth, unordered_set<char>& survival);
        char& operator [] (int i);
        const char& operator [] (int i) const;
};