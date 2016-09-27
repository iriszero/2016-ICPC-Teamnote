template <class T> class Fraction {
public:
    T nu, de;
public:
    Fraction<T>() {
        Fraction<T>(0);
    }
    Fraction<T>(T nu, T de= 1) {
        this->nu = nu; this->de = de;
    }
    Fraction<T>& operator+(const Fraction &other) const {
        Fraction<T> res;
        T a = this->nu * other.de + other.nu * this->de;
        T b = this->de * other.de;
        T g = gcd(a, b);
        res.nu = a / g;
        res.de = b / g;
        return res;
    }
    Fraction<T> operator-(const Fraction &other) const {
        Fraction<T> res;
        T a = this->nu * other.de - other.nu * this->de;
        T b = this->de * other.de;
        T g = gcd(a, b);
        res.nu = a / g;
        res.de = b / g;
        return res;
    }
    Fraction<T> operator*(const Fraction &other) const {
        Fraction<T> res;
        T a = this->nu * other.nu;
        T b = this->de * other.de;
        T g = gcd(a, b);
        res.nu = a / g;
        res.de = b / g;
        return res;
    }
    Fraction<T> operator/(const Fraction &other) const {
        Fraction<T> res;
        T a = this->nu * other.de;
        T b = this->de * other.nu;
        T g = gcd(a, b);
        res.nu = a / g;
        res.de = b / g;
        return res;
    }
    Fraction& operator+= (const Fraction &other) {
        T a = this->nu * other.de + other.nu * this->de;
        T b = this->de * other.de;
        T g = gcd(a, b);
        this->nu = a / g;
        this->de = b / g;
        return (*this);
    }
    Fraction& operator-= (const Fraction &other) {
        T a = this->nu * other.de - other.nu * this->de;
        T b = this->de * other.de;
        T g = gcd(a, b);
        this->nu = a/g;
        this->de = b/g;
        return (*this);
    }
    Fraction& operator*= (const Fraction &other) {
        T a = this->nu * other.nu;
        T b = this->de * other.de;
        T g = gcd(a, b);
        this->nu = a/g;
        this->de = b/g;
        return (*this);
    }
    Fraction operator/= (const Fraction &other) {
        T a = this->nu * other.de;
        T b = this->de * other.nu;
        T g = gcd(a ,b);
        this->nu = a/g;
        this->de = b/g;
        return (*this);
    }
    bool operator==(const Fraction &other) const {
        return (this->nu == other.nu) && (this->de == other.de);
    }
    bool operator!=(const Fraction &other) const {
        return !(*this == other);
    }
    bool operator<(const Fraction &other) const {
        return this->nu * other.de < this->de * other.nu;
    }
    bool operator>(const Fraction &other) const {
        return this->nu * other.de > this->de * other.nu;
    }
    bool operator<=(const Fraction &other) const {
        return this->nu * other.de <= this->de * other.nu;
    }
    bool operator>=(const Fraction &other) const {
        return this->nu * other.de >= this->de * other.nu;
    }
    Fraction<ll> operator-() {
        return (*this) * Fraction<T>(-1);
    }
    operator T(){
        return nu / de;
    }
    Fraction<ll>& operator=(const Fraction<ll> &other) {
        nu = other.nu;
        de = other.de;
        return (*this);
    }
    friend ostream & operator<<(ostream &os, const Fraction<T> &other) {
        os << other.nu << " / " << other.de;
        return os;
    }
};
