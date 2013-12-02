#ifndef TELLER_H
#define TELLER_H

class Teller
{
public:
    Teller(const QString& file_name);
    ~Teller() {}

    int get20() const { return _20; }
    int get50() const { return _50; }
    int get100() const { return _100; }
    int get200() const { return _200; }
    int get500() const { return _500; }
    void set20(const int n) { _20 = n; }
    void set50(const int n) { _50 = n; }
    void set100(const int n) { _100 = n; }
    void set200(const int n) { _200 = n; }
    void set500(const int n) { _500 = n; }

private:
    int _20;
    int _50;
    int _100;
    int _200;
    int _500;
};

#endif // TELLER_H
