#include<iostream>
#include<string>
#include<iomanip>
#include<ctime>
#include<cstdlib>
#include<limits>

//Bool default = false
// if (default) => ko lam gi ca tai if() o day check xem bool = true hay ko
class PhuongTien{
    private:
    int MaXe;
    std::string LoaiXe;
    int GioVao;
    int ThoiGianDo;

    
    public:
    PhuongTien();
    PhuongTien(int Ma, std::string Loai, int Gio, int ThoiGian);

    int LayMaXe() const;
    std::string LayLoaiXe() const;
    double TinhPhi() const;
    void HienThi() const;
};

PhuongTien::PhuongTien(){
    MaXe = 0;
    LoaiXe = "";
    GioVao = 0;
    ThoiGianDo = 0;
}
PhuongTien::PhuongTien(int Ma, std::string Loai, int Gio, int ThoiGian){
    MaXe = Ma;
    LoaiXe = Loai;
    GioVao = Gio;
    ThoiGianDo = ThoiGian; 
}
int PhuongTien::LayMaXe() const{
    return MaXe;
}
std::string PhuongTien::LayLoaiXe() const{
    return LoaiXe;
}
double PhuongTien::TinhPhi() const{
    double gia = (LoaiXe=="Car")? 6.0 : (LoaiXe=="Motorcycle")? 4.0 : 2.0;
    bool GioCaoDiem = (GioVao>=6 && GioVao<=10) || (GioVao>=15 && GioVao<=19); //<- GioCaoDiem = true neu thoa man 1 trong 2
    double tong;

    for(int i = 0; i<ThoiGianDo; i++){
        if(i<2){
            if(GioCaoDiem){
                tong+= gia*1.30;
            }
            else{
                tong+= gia*0.95;
            }
        }
        else{
            tong+= gia*0.9;
        }
    }
    return tong;
}
void PhuongTien::HienThi() const{
    std::cout << "ID: " << MaXe << "||Loai xe: " << LoaiXe << "||Gio vao: " <<GioVao <<"h"
              << "||Thoi gian do: " << ThoiGianDo << "h" << '\n'
              << "Phi Do Xe: $" << std::fixed << std::setprecision(2) << TinhPhi() << '\n';
}


class BaiDoXe{
    private:
    int ID_BaiDoXe;
    char KichCo;
    PhuongTien PT1, PT2, PT3; //<- Doi tuong xe
    bool CoPT1,CoPT2,CoPT3; //<- all = false, kiem tra trang thai trong

    public:
    BaiDoXe();
    BaiDoXe(int ID, char size);

    int LayMa() const;
    bool ThemXe(PhuongTien v);
    bool XoaXe(int MaXe);
    void HienThi() const;
    bool CoLoai(std::string Loai, int& dem, double& tong) const; //<- dung de hien thi loai xe minh can
};

BaiDoXe::BaiDoXe(){
    ID_BaiDoXe = 0;
    char KichCo = 's';
    CoPT1 = false, CoPT2 = false, CoPT3 = false;
}
BaiDoXe::BaiDoXe(int ID, char size){
    ID_BaiDoXe = ID;
    KichCo = size;
    CoPT1 = false, CoPT2 = false, CoPT3 = false;
}
int BaiDoXe::LayMa()const{
    return ID_BaiDoXe;
}
bool BaiDoXe::ThemXe(PhuongTien v){
    int Cap = (KichCo=='S')? 1 : (KichCo=='M')? 2 : 3; //<- Size = S => 1 xe, Size = M => 2 xe, Size = L => 3 xe
    if(Cap>=1 && !CoPT1){ //Check neu !CoPT1 = true ko (nghia la check neu co phuong tien 1 khong, neu !CoPT1 = true nghia la chua co)
        PT1 = v;
        CoPT1 = true;
        return true;
    }
    if(Cap>=2 && !CoPT2){
        PT2 = v;
        CoPT2 = true;
        return true;
    }
    if(Cap>=3 && !CoPT3){
        PT3 = v;
        CoPT3 = true;
        return true;
    }
    return false;
}
bool BaiDoXe::XoaXe(int MaXe){
    if(CoPT1 && PT1.LayMaXe() == MaXe){
        if(CoPT2){
            PT1 = PT2;
            if(CoPT3){
                PT2 = PT3;
                CoPT3 = false;
            }
            else{
                CoPT2 = false;
            }
        }
        else{
            CoPT1 = false; //Co nghia la, khi xoa pt1, ta se day pt2 xuong slot cua pt1 (neu co) roi xoa slot cua pt2
            //lam tuong tu neu co slot cua pt3.
            //neu khong co pt2 ngay tu day thi xoa luon slot cua pt1.
        }
        return true;
    }
    if(CoPT2 && PT2.LayMaXe() == MaXe){
        if(CoPT3){
            PT2 = PT3;
            CoPT3 = false;
        }
        else{
            CoPT2 = false;
        }
        return true;
    }
    if(CoPT3 && PT3.LayMaXe() == MaXe){
        CoPT3 = false;
        return true;
    }
    return false;
}
void BaiDoXe::HienThi()const{
    int Cap = (KichCo=='S')? 1 : (KichCo=='M')? 2 : 3;
    int SoLuongXe = CoPT1 + CoPT2 + CoPT3; //bool = 0/1 nen cong duoc
    std::cout << "Bai: " << ID_BaiDoXe << "(" << KichCo << ")"
              << "||So xe: " << SoLuongXe << "/" << Cap << '\n'; 
    if(CoPT1){
        PT1.HienThi();
    }
    if(CoPT2){
        PT2.HienThi();
    }
    if(CoPT2){
        PT3.HienThi();
    }
}
bool BaiDoXe::CoLoai(std::string Loai, int& dem, double& tong) const{
    dem = 0; tong = 0;
    if (CoPT1 && PT1.LayLoaiXe() == Loai){
        dem++;
        tong+=PT1.TinhPhi();
    }
    if (CoPT2 && PT2.LayLoaiXe() == Loai){
        dem++;
        tong+=PT2.TinhPhi();
    }
    if (CoPT3 && PT3.LayLoaiXe() == Loai){
        dem++;
        tong+=PT3.TinhPhi();
    }
    return dem > 0;
}

class SystemInterface{
    private: 
    BaiDoXe BD1, BD2, BD3;
    bool CoBD1, CoBD2, CoBD3;

    public:
    SystemInterface();
    void runMenu();
    void TaoBaiDo();
    void ThemXe();
    void XoaBaiDo();
    void LayXeRa();
    void HienThiTatCa();
    void HienThiTheoBai();
    void LietKeXeTheoLoai();
    void PhiTrungBinh();
};

SystemInterface::SystemInterface(){
    CoBD1 = false, CoBD2 = false, CoBD3 = false;
}
void SystemInterface::TaoBaiDo(){
            int Ma;
            char KT;
            std::cout << "Ma bai: ";
            std:: cin >> Ma;
            std::cout << "Kich Co: ";
            std:: cin >> KT;
            if(!CoBD1){ //Check neu da co bai do hay chua
                BD1 = BaiDoXe(Ma, KT);
                CoBD1 = true;
            }
            else if(!CoBD2){
                BD2 = BaiDoXe(Ma, KT);
                CoBD2 = true;
            }
            else{
                BD3 = BaiDoXe(Ma, KT);
                CoBD3 = true;
            }
            std::cout<< "Da Tao Bai\n";
}
void SystemInterface::ThemXe(){
            int MaXe;
            int GioVao;
            int ThoiGianDo;
            std::string LoaiXe;

            std::cout << "Ma xe: "; std::cin >> MaXe;
            std::cout << "Loai (Car/Motorcycle/Bicycle): "; std::cin >> LoaiXe;
            std::cout << "Gio vao (0-23): "; std::cin >> GioVao;
            std::cout << "Thoi gian do (1-23): "; std::cin >> ThoiGianDo;

            PhuongTien v(MaXe,LoaiXe,GioVao,ThoiGianDo);
            bool check = false;
            if(CoBD1 && !check){       //Check tung bai do mot. False -> Bai do day.
                check = BD1.ThemXe(v);
            }
            if(CoBD2 && !check){
                check = BD2.ThemXe(v);
            }
            if(CoBD3 && !check){
                check = BD1.ThemXe(v);
            }

            if(check){
                std::cout<< "Da them xe " << MaXe << "||Kinh phi: " << std::fixed << std::setprecision(2) << v.TinhPhi() <<'\n';
            }
            else{
                std::cout<< "Tat ca bai do da day.\n";
            }
}
void SystemInterface::XoaBaiDo(){
    int MaBai;
    std::cout<< "Ma bai do can xoa: "; std::cin >> MaBai;
    if(CoBD1 && BD1.LayMa() == MaBai){
        if(CoBD2){
            BD1 = BD2;
            if(CoBD3){
                BD2 = BD3;
                CoBD3 = false;
            }
            else{
                CoBD2 = false;
            }
        }
        else{
            CoBD1 = false;
        }
        std::cout << "Da xoa bai do " << MaBai <<'\n';
    }
    if(CoBD2 && BD2.LayMa() == MaBai){
        if(CoBD3){
            BD2 = BD3;
            CoBD3 = false;
        }
        else{
            CoBD2 = false;
        }
        std::cout<< "Da xoa bai do " << MaBai << '\n';
    }
    if(CoBD3 && BD3.LayMa() == MaBai){
        CoBD3 = false;
        std::cout<< "Da xoa bai do " << MaBai << '\n';
    }
}
void SystemInterface::LayXeRa(){
    int MaXe;
    std::cout << "Nhap ma xe can lay ra: ";
    std::cin >> MaXe;
    bool check = false;
    if(!check && CoBD1){
        check = BD1.XoaXe(MaXe);
    }
    if(!check && CoBD2){
        check = BD2.XoaXe(MaXe);
    }
    if(!check && CoBD3){
        check = BD3.XoaXe(MaXe);
    }
    if(check){
        std::cout<<"Da lay xe\n";
    }
    else{
        std::cout<<"Xe khong ton tai\n";
    }

}
void SystemInterface::HienThiTatCa(){
    if(CoBD1){
        BD1.HienThi();
    }
    if(CoBD2){
        BD2.HienThi();
    }
    if(CoBD3){
        BD3.HienThi();
    }
}
void SystemInterface::HienThiTheoBai(){
    int MaBai;
    std::cout << "Nhap ma bai: "; std::cin >> MaBai;
    if(BD1.LayMa() == MaBai && CoBD1){
        BD1.HienThi();
    }
    if(BD2.LayMa() == MaBai && CoBD2){
        BD2.HienThi();
    }
    if(BD3.LayMa() == MaBai && CoBD3){
        BD3.HienThi();
    }
}
void SystemInterface::LietKeXeTheoLoai(){
    std::string LoaiXe;
    std::cout << "Loai xe can tim: ", std::cin >> LoaiXe;
    int dem;
    double tong;
    if(CoBD1 && BD1.CoLoai(LoaiXe, dem, tong)){
        BD1.HienThi();
    }
    if(CoBD2 && BD2.CoLoai(LoaiXe, dem, tong)){
        BD2.HienThi();
    }
    if(CoBD3 && BD3.CoLoai(LoaiXe, dem, tong)){
        BD3.HienThi();
    }
}
void SystemInterface::PhiTrungBinh(){
    std::string LoaiXe[3] = {"Car","Motorcycle","Bicycle"};
    for(int i = 0; i<3;i++){
        int dem = 0; //dem va tong o day chua duoc gan gia tri nen se tu dong co mot gia tri ngau nhien
        double tong = 0;
        int d;
        double s;
        if(CoBD1){
            BD1.CoLoai(LoaiXe[i],d,s); //d vs s ko can gan do khi vao trong CoLoai thi no da cho dem vs tong = 0 r.
            dem+=d;
            tong+=s;
        }
        if(CoBD2){
            BD2.CoLoai(LoaiXe[i],d,s);
            dem+=d;
            tong+=s;
        }
        if(CoBD3){
            BD3.CoLoai(LoaiXe[i],d,s);
            dem+=d;
            tong+=s;
        }
        if(dem!=0){
            std::cout<< LoaiXe[i] << " co " << dem << " xe" << '\n'
            << "||Phi trung binh: " << std::fixed << std::setprecision(2) << tong/dem << '\n';
        }
        else{
            std::cout << "Khong co '" << LoaiXe[i] << "'\n"; 
        }
    }
}

void SystemInterface::runMenu(){
    int chon;
    do{
        std::cout << "---------------Quan Ly Bai Do Xe---------------" << '\n'
        << "1. Tao bai do\n"
        << "2. Them xe\n"
        << "3. Xoa bai do\n"
        << "4. Lay xe ra\n"
        << "5. Hien thi tat ca bai do\n"
        << "6. Hien thi xe theo bai\n"
        << "7. Liet ke xe theo loai\n"
        << "8. Bao cao phi trung binh\n"
        << "9. Thoat\n"
        << "-----------------------------------------------\n";
        std::cout << "Chon: ";
        std::cin >> chon;
        switch(chon){ //Bang cach nao do khi ma dung switch thi ko viet duoc ma vao nhu thuong?
        case 1:
            TaoBaiDo();
            break;
        case 2:
            ThemXe();
            break;
        case 3:
            XoaBaiDo();
            break;
        case 4:
            LayXeRa();
            break;
        case 5:
            HienThiTatCa();
            break;
        case 6:
            HienThiTheoBai();
            break;
        case 7:
            LietKeXeTheoLoai();
            break;
        case 8:
            PhiTrungBinh();
            break;
        }
    }while(chon!=9);
}



int main(){
    SystemInterface Ui;
    Ui.runMenu();
    return 0;
}