#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

class Virus {
    protected:
        float ktrchungrate;
        float trchungnherate;
        float trchungnangrate;
        float tuvongrate;

        float tuvongtbrate;
        float deathrate;
        float survivalrate;

        bool trieuchungnang = false;
        bool tuvong = false;
        bool tiemVaccine = false;
    public:
    virtual ~Virus() {}
    virtual void ChoNhiem() = 0;      
    virtual string TenVirus() = 0;    

    void TaoKhaNangMienDich(int level) {
        if (!tiemVaccine)
        {
          switch(level) {
            case 0: // Thấp
                ktrchungrate   = 0.05f;
                trchungnherate = 0.15f;
                trchungnangrate= 0.80f;
                tuvongrate     = 1.00f;
                break;
            case 1: // Trung bình
                ktrchungrate   = 0.10f;
                trchungnherate = 0.40f;
                trchungnangrate= 0.50f;
                tuvongrate     = 0.70f;
                break;
            case 2: // Cao
                ktrchungrate   = 0.50f;
                trchungnherate = 0.35f;
                trchungnangrate= 0.15f;
                tuvongrate     = 0.50f;
                break;
            default:
                cout<<"Kha nang mien dich khong phu hop!";
                break;
            }
        }
        else
        {
          switch(level) {
            case 0: // Thấp
                ktrchungrate   = 0.10f;
                trchungnherate = 0.40f;
                trchungnangrate= 0.50f;
                tuvongrate     = 0.80f;
                break;
            case 1: // Trung bình
                ktrchungrate   = 0.20f;
                trchungnherate = 0.50f;
                trchungnangrate= 0.30f;
                tuvongrate     = 0.60f;
                break;
            case 2: // Cao
                ktrchungrate   = 0.70f;
                trchungnherate = 0.25f;
                trchungnangrate= 0.05f;
                tuvongrate     = 0.40f;
                break;
            default:
                cout<<"Kha nang mien dich khong phu hop!";
                break;
            }
        }
    }

    void ChoTiemVaccine()
    {
        tiemVaccine = true;
    }

    void CalculateRate() {
        deathrate     = tuvongrate * tuvongtbrate;
        survivalrate  = 1 - deathrate;
        ktrchungrate  *= survivalrate;
        trchungnherate*= survivalrate;
        trchungnangrate*= survivalrate;
    }

    bool TrieuChungNang()
    {
        float r = static_cast<float>(rand()) / RAND_MAX;
        if (r < ktrchungrate + trchungnherate + trchungnangrate && r > ktrchungrate + trchungnherate)
        {
            return true;
        }
        return false;
    }

    bool TuVong()
    {
        float r = static_cast<float>(rand()) / RAND_MAX;
        if (r < ktrchungrate + trchungnherate + trchungnangrate + tuvongrate && r > ktrchungrate + trchungnherate + trchungnangrate)
        {
            return true;
        }
        return false;
    }

    void XuatTrieuChung() {
        float r = static_cast<float>(rand()) / RAND_MAX;
        cout << "  - r = " << r << "\n";
        cout << "  Trieu chung virus " << TenVirus() << ": ";
        if (r < ktrchungrate)
            cout << "Khong co trieu chung.\n";
        else if (r < ktrchungrate + trchungnherate)
            cout << "Trieu chung nhe.\n";
        else if (r < ktrchungrate + trchungnherate + trchungnangrate)
            cout << "Trieu chung nang.\n";
        else
            cout << "Da tu vong.\n";
    }
};

class Covid : public Virus {
    public:
        void ChoNhiem() override {
            tuvongtbrate = 0.05f;
            CalculateRate();
        }
        string TenVirus() override { return "Covid"; }
};

class Ebola : public Virus {
    public:
        void ChoNhiem() override {
            tuvongtbrate = 0.50f;
            CalculateRate();
        }
        string TenVirus() override { return "Ebola"; }
};

class HIV : public Virus {
    public:
        void ChoNhiem() override {
            tuvongtbrate = 0.90f;
            CalculateRate();
        }
        string TenVirus() override { return "HIV"; }
};

class VatChu {
    public:
        string mavatchu;
        int khanangmiendich; 

        void Nhap() {
            cout << "Nhap ma vat chu: ";
            cin >> mavatchu;
            cout << "Nhap kha nang mien dich cua vat chu (0.Thap, 1.Trung binh, 2.Cao): ";
            cin >> khanangmiendich;
        }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int n;
    cout << "Nhap so luong vat chu: ";
    cin >> n;

    vector<VatChu> vatchuList(n);

    for (int i = 0; i < n; ++i) {
        cout << "\n=== Vat chu thu " << i+1 << " ===\n";
        vatchuList[i].Nhap();
    }

    for (int i = 0; i < n; ++i) {
        cout << "\n*** Vat chu " << vatchuList[i].mavatchu
             << " (mien dich=" << vatchuList[i].khanangmiendich << ") ***\n";

        vector<Virus*> virusList = {
            new Covid(),
            new Ebola(),
            new HIV()
        };

        for (int j = 0; j < virusList.size(); ++j) {
            Virus* v = virusList[j];
            v->TaoKhaNangMienDich(vatchuList[i].khanangmiendich);
            v->ChoNhiem();
            v->XuatTrieuChung();
            delete v;
        }
    }
    
    vatchuList.clear();
    cout<<"Nhap so luong vat chu moi: ";
    cin>>n;

    vector<VatChu> vatchuNewList(n);

    int soTrieuChungNang = 0;
    int soTuVong = 0;

    for (int i = 0; i < n; ++i) {
        cout << "\n=== Vat chu thu " << i+1 << " ===\n";
        vatchuNewList[i].Nhap();
    }

    for (int i = 0; i < n; ++i) {
        vector<Virus*> virusList = {
            new Covid(),
            new Ebola(),
            new HIV()
        };

        bool daTrieuChungnang = false;
        bool daTuVong = false;

        for (int j = 0; j < virusList.size(); ++j) {
            Virus* v = virusList[j];
            v->ChoTiemVaccine();
            v->TaoKhaNangMienDich(vatchuNewList[i].khanangmiendich);
            v->ChoNhiem();
            v->XuatTrieuChung();
            if(!daTrieuChungnang && v->TrieuChungNang())
            {
                soTrieuChungNang++;
                daTrieuChungnang = true;
            }
            if(!daTuVong && v->TuVong())
            {
                soTuVong++;
                daTuVong = true;
            }
        }
    }
    
    cout<<"So luong dong vat trieu chung nang: "<<soTrieuChungNang<<endl;
    cout<<"So luong dong vat da tu vong: "<<soTuVong<<endl;

    return 0;
}
