class Writer {
    protected:
        virtual ~Writer() = default;
        Writer& operator = (const Writer&) = delete;
    public:
};