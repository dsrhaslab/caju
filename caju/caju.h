
class Caju{
public:
    Caju();
    Caju(Caju &&) = default;
    Caju(const Caju &) = default;
    Caju &operator=(Caju &&) = default;
    Caju &operator=(const Caju &) = default;
    ~Caju();

private:
    
};
