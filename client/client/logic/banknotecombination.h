#ifndef BANKNOTECOMBINATION_H
#define BANKNOTECOMBINATION_H

class BanknoteCombination {
private:
    int _10;
    int _20;
    int _50;
    int _100;
    int _200;
    int _500;
public:

    BanknoteCombination(int b10, int b20, int b50, int b100, int b200, int b500);
    ~BanknoteCombination() {}

    int get10() const { return _10; }
    int get20() const { return _20; }
    int get50() const { return _50; }
    int get100() const { return _100; }
    int get200() const { return _200; }
    int get500() const { return _500; }
    void set10(const int n) { _10 = n; }
    void set20(const int n) { _20 = n; }
    void set50(const int n) { _50 = n; }
    void set100(const int n) { _100 = n; }
    void set200(const int n) { _200 = n; }
    void set500(const int n) { _500 = n; }
};


#endif // BANKNOTECOMBINATION_H
