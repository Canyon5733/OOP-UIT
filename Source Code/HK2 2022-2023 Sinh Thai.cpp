#include <iostream>
#include <vector>
using namespace std;

class ConVat
{
    protected:
        int giaidoan1;
        int giaidoan2;
        int giaidoan3;
        int giaidoan4;
        string loaidongvat;
    public:
        virtual void Nhap() = 0;
        string getLoaiDongVat()
        {
            return loaidongvat;
        }
        int getGiaiDoan1()
        {
            return giaidoan1;
        }
        int getGiaiDoan2()
        {
            return giaidoan2;
        }
        int getGiaiDoan3()
        {
            return giaidoan3;
        }
        int getGiaiDoan4()
        {
            return giaidoan4;
        }
        virtual int getGiaidoan5()
        {
            return -1;
        }
};

class ConMuoi: public ConVat{
    public:
        void Nhap()
        {
            cout<<"Nhap thong tin vong doi con muoi (ngay): ";
            cin>>giaidoan1>>giaidoan2>>giaidoan3>>giaidoan4;
            loaidongvat = "Muoi";
        }
};

class ConEch: public ConVat{
    private:
        int giaidoan5;
    public:
        void Nhap()
        {
            cout<<"Nhap thong tin vong doi con ech (tuan): ";
            cin>>giaidoan1>>giaidoan2>>giaidoan3>>giaidoan4>>giaidoan5;
            loaidongvat = "Ech";
        }
        int getGiaidoan5()
        {
            return giaidoan5;
        }
};

class ConBuom: public ConVat{
    public:
        void Nhap()
        {
            cout<<"Nhap thong tin vong doi con buom (ngay): ";
            cin>>giaidoan1>>giaidoan2>>giaidoan3>>giaidoan4;
            loaidongvat = "Buom";
        }
};

int main()
{
    int n;
    cout<<"Nhap so luong con vat: ";
    cin>>n;
    ConVat* cv = nullptr;
    vector<ConVat*> animalList;
    while(n)
    {
        int choice;
        cout<<"Nhap loai dong vat (1. Muoi, 2. Buom, 3. Ech): ";
        cin>>choice;
        if (choice == 1)
        {
            cv = new ConMuoi();
        }
        else if (choice == 2)
        {
            cv = new ConBuom();
        }
        else if (choice == 3)
        {
            cv = new ConEch();
        }
        cv->Nhap();
        animalList.push_back(cv);
        n--;
    }

    cout<<"Danh sach nhung con vat khong tuan theo quy luat thong thuong: "<<endl;
    bool coMuoi = false;
    bool coEch = false;
    bool coBuom = false;
    for (int i = 0; i < animalList.size(); i++)
    {
        if(animalList[i]->getLoaiDongVat() == "Muoi")
        {
            coMuoi = true;
            if (animalList[i]->getGiaiDoan1() > 3 || (animalList[i]->getGiaiDoan2() < 4 || animalList[i]->getGiaiDoan2() > 10 )|| (animalList[i]->getGiaiDoan3() < 2 || animalList[i]->getGiaiDoan3()> 3) || (animalList[i]->getGiaiDoan4() < 5 || animalList[i]->getGiaiDoan4() > 8))
            {
                cout<<"Vi tri cua muoi thu: "<<i<<endl;
            }
        }
        else if (animalList[i]->getLoaiDongVat() == "Ech")
        {
            coEch = true;
            if (animalList[i]->getGiaiDoan1() < 1 || animalList[i]->getGiaiDoan1() > 3 || animalList[i]->getGiaiDoan2() != 4 || animalList[i]->getGiaiDoan3() < 6 || animalList[i]->getGiaiDoan3() > 9 || animalList[i]->getGiaiDoan4() < 1 || animalList[i]->getGiaiDoan4() > 4 || animalList[i]->getGiaidoan5() < 70 || animalList[i]->getGiaidoan5() > 140)
            {
                cout<<"Vi tri cua ech thu: "<<i<<endl;
            }
        }
        else if (animalList[i]->getLoaiDongVat() == "Buom")
        {
            coBuom = true;
            if (animalList[i]->getGiaiDoan1() < 3 || animalList[i]->getGiaiDoan1() > 8 || animalList[i]->getGiaiDoan2() < 15 || animalList[i]->getGiaiDoan2() > 16 || animalList[i]->getGiaiDoan3() != 10 || animalList[i]->getGiaiDoan4() < 2 || animalList[i]->getGiaiDoan4() > 3)
            {
                cout<<"Vi tri cua buom thu: "<<i<<endl;
            }
        }
    }

    if (coMuoi && coBuom && coEch)
    {
        cout<<"Khu vuc sinh thai co tinh da dang sinh hoc"<<endl;
    }
    return 0;
}