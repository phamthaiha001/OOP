#include<iostream>
#include<string>
#include<iomanip>
#include<ctime>
#include <cstdlib>

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
    static const int PT_ToiDa = 3;
    PhuongTien PT[PT_ToiDa];
    int SoLuong_PT;

    public:
    BaiDoXe();
    BaiDoXe(int ID, char size);

    int LayMa() const;
    bool DaDay() const;
    bool ThemXe(const PhuongTien v);
    bool XoaXe(int MaXe);
    int Index_PT(int MaXe)const;
    void HienThi() const;

    bool CoLoai(std::string Loai, int& dem, double& tong) const; //<- dung de hien thi loai xe minh can
};

BaiDoXe::BaiDoXe(){
    ID_BaiDoXe = 0;
    char KichCo = 's';
    SoLuong_PT = 0;
}
BaiDoXe::BaiDoXe(int ID, char size){
    ID_BaiDoXe = ID;
    KichCo = size;
    SoLuong_PT = 0;
}
int BaiDoXe::LayMa()const{
    return ID_BaiDoXe;
}
bool BaiDoXe::DaDay() const{
    int Cap = (KichCo=='S')? 1 : (KichCo=='M')? 2 : 3;
    return SoLuong_PT >= Cap; //check neu ma DaDay hay chua, true = day, false = chua
}
bool BaiDoXe::ThemXe(PhuongTien v){
    int Cap = (KichCo=='S')? 1 : (KichCo=='M')? 2 : 3; //<- Size = S => 1 xe, Size = M => 2 xe, Size = L => 3 xe
    if(SoLuong_PT<Cap){ // '<' do mang co ca 0, 0 tinh la mot phan tu
        PT[SoLuong_PT] = v;
        SoLuong_PT++;
        return true;
    }
    return false;
}
int BaiDoXe::Index_PT(int MaXe)const{
    for(int i = 0; i< SoLuong_PT;i++){
        if(PT[i].LayMaXe() == MaXe){
            return i;//tra ve chi so index
        }
    }
    return -1;
}
bool BaiDoXe::XoaXe(int MaXe){
    int id = Index_PT(MaXe);//tim xe theo id trong mang
    if(id==-1){
        return false;
    }
    for(int i = 0;i< SoLuong_PT-1;i++){//loại trừ bãi đỗ cuối do ko cần đẩy lùi cái đó
        PT[i] = PT[i+1];
    }
    SoLuong_PT--;
    return true;
}
void BaiDoXe::HienThi()const{
    int Cap = (KichCo=='S')? 1 : (KichCo=='M')? 2 : 3;
    std::cout << "Bai: " << ID_BaiDoXe << "(" << KichCo << ")"
              << "||So xe: " << SoLuong_PT << "/" << Cap << '\n'; 
    for(int i = 0; i < SoLuong_PT;i++){
        PT[i].HienThi();
    }
}
bool BaiDoXe::CoLoai(std::string Loai, int& dem, double& tong) const{
    dem = 0; tong = 0;
    for(int i = 0; i < SoLuong_PT; i++){
        if(PT[i].LayLoaiXe() == Loai){
            dem++;
            tong+=PT[i].TinhPhi();
        }
    }
    return dem > 0;
}

class SystemInterface{
    private: 
    static const int BaiDo_Max = 10;
    BaiDoXe baidoxe[BaiDo_Max];
    int SoLuong_BaiDo;

    public:
    SystemInterface();
    void runMenu();
    bool isParkIDExists(int pID) const;
    bool isVehicleIDExists(int vID) const;
    int generateRandomID() const;


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
    SoLuong_BaiDo = 0;
}

bool SystemInterface::isParkIDExists(int pID) const{
    for(int i = 0; i < SoLuong_BaiDo;i++){
        if(baidoxe[i].LayMa() == pID){
            return true;
        }
    }
    return false;
}
bool SystemInterface::isVehicleIDExists(int vID) const{
    for(int i = 0; i < SoLuong_BaiDo;i++){
        if(baidoxe[i].Index_PT(vID) != -1){//Index_PT return -1 neu ko co
            return true;
        }
    }
    return false;
}
int SystemInterface::generateRandomID() const{
    srand(time(NULL));
    int id = rand();
    return id;
}
void SystemInterface::TaoBaiDo(){
        if(SoLuong_BaiDo>BaiDo_Max){
            std::cout << "Khong the tao them bai do xe.\n";
            return;
        }
        int Ma;
        char KT;
        std::cout << "Ma bai: ";
        std:: cin >> Ma;
        while (!(std::cin >> Ma)){//dung cho int/so 
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Du lieu khong hop le. Nhap lai ma bai: ";
        }   
        if(isParkIDExists(Ma)){
            Ma = generateRandomID();
            while(isParkIDExists(Ma)){//de phong van tao ra ma da ton tai roi;
                Ma = generateRandomID();
            }
            std::cout<< "Ma bai da ton tai. Ma moi duoc gan se la: " << Ma << '\n';
        }

        std::cout << "Kich Co(S/M/L): ";
        std:: cin >> KT;
        while (KT != 'S' && KT != 'M' && KT != 'L') {
            std::cout << "Kich co khong hop le. Nhap lai: ";
            std::cin >> KT;
        }

        baidoxe[SoLuong_BaiDo] = BaiDoXe(Ma,KT);
        SoLuong_BaiDo++;
    std::cout<< "Da Tao Bai\n";
}
void SystemInterface::ThemXe(){
            int MaXe;
            int GioVao;
            int ThoiGianDo;
            std::string LoaiXe;

            std::cout << "Ma xe: ";
            while (!(std::cin >> MaXe)){
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Du lieu khong hop le. Nhap lai ma xe: ";
            }
            if(isVehicleIDExists(MaXe)){
                MaXe = generateRandomID();
                while(isVehicleIDExists(MaXe)){//de phong van tao ra ma da ton tai roi;
                    MaXe = generateRandomID();
                }
            std::cout<< "Ma bai da ton tai. Ma moi duoc gan se la: " << MaXe << '\n';
        }   

            std::cout << "Loai (Car/Motorcycle/Bicycle): "; std::cin >> LoaiXe;
            while (LoaiXe != "Car" && LoaiXe != "Motorcycle" && LoaiXe != "Bicycle"){
                std::cout << "Loai xe khong hop le. Nhap lai: ";
                std::cin >> LoaiXe;
            }
            std::cout << "Gio vao (0-23): ";
            while (!(std::cin >> GioVao) || GioVao<0 || GioVao > 23){
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Du lieu khong hop le. Nhap lai gio vao: ";
            }

            std::cout << "Thoi gian do (1-23): ";
            while (!(std::cin >> ThoiGianDo) || ThoiGianDo<1 || ThoiGianDo > 23){
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Du lieu khong hop le. Nhap lai thoi gian do: ";
            }


            PhuongTien v(MaXe,LoaiXe,GioVao,ThoiGianDo);
            bool check = false;

            for(int i=0;i<SoLuong_BaiDo;i++){
                if(!baidoxe[i].DaDay()){
                    check = baidoxe[i].ThemXe(v);
                }
            if(check){
                std::cout<< "Da them xe " << MaXe << "||Kinh phi: " << std::fixed << std::setprecision(2) << v.TinhPhi() <<'\n';
            }
            else{
                std::cout<< "Tat ca bai do da day.\n";
                return;
            }
        }
}
void SystemInterface::XoaBaiDo(){
    int MaBai;
    std::cout<< "Ma bai do can xoa: ";
    while (!(std::cin >> MaBai)){
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Du lieu khong hop le. Nhap lai ma bai: ";
    }
    int id = -1;
    for(int i = 0; i<SoLuong_BaiDo;i++){
        if(baidoxe[i].LayMa() == MaBai){
            id = i;
            break;
        }
    }
    if(id!=-1){
        for(int i = id; i<SoLuong_BaiDo;i++){
            baidoxe[i] = baidoxe[i+1];
        }
        SoLuong_BaiDo--;
        std::cout<< "Xoa bai do thanh cong.\n";
    }
    else{
        std::cout<< "Bai do khong ton tai.\n";
    }

}
void SystemInterface::LayXeRa(){
    int MaXe;
    std::cout << "Nhap ma xe can lay ra: ";
    while (!(std::cin >> MaXe)){
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Du lieu khong hop le. Nhap lai ma xe: ";
    }

    bool check = false;
    for(int i = 0; i < SoLuong_BaiDo;i++){
        if(baidoxe[i].XoaXe(MaXe)){
            check = true;
            break;
        }
    }

    if(check){
        std::cout<<"Da lay xe\n";
    }
    else{
        std::cout<<"Xe khong ton tai\n";
    }

}
void SystemInterface::HienThiTatCa(){
    if(SoLuong_BaiDo > 0){
        for(int i = 0; i<SoLuong_BaiDo;i++){
            baidoxe[i].HienThi();
            std::cout << "----------------\n";
        }
    }
    else{
        std::cout<< "Khong co bai do";
    }
}
void SystemInterface::HienThiTheoBai(){
    int MaBai;
    std::cout << "Nhap ma bai: ";
        while (!(std::cin >> MaBai)){
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Du lieu khong hop le. Nhap lai ma bai: ";
        } 
    bool check = false;
    for(int i = 0; i<SoLuong_BaiDo;i++){
        if(baidoxe[i].LayMa() == MaBai){
            baidoxe[i].HienThi();
            check = true;
        }
    }
    if(!check){
        std::cout << "Ko tim thay bai\n";
    }
}
void SystemInterface::LietKeXeTheoLoai(){
    std::string LoaiXe;
    std::cout << "Loai xe can tim: ", std::cin >> LoaiXe;
    while (LoaiXe != "Car" && LoaiXe != "Motorcycle" && LoaiXe != "Bicycle"){
        std::cout << "Loai xe khong hop le. Nhap lai: ";
        std::cin >> LoaiXe;
    }
    int DemTong = 0;


    for(int i = 0; i < SoLuong_BaiDo;i++){
        int dem;
        double tong;//ko can dem = 0, tong = 0 vi cho vao CoLoai() roi
        if(baidoxe[i].CoLoai(LoaiXe,dem,tong)){
            baidoxe[i].HienThi();
            DemTong++;
        }
    }
    if(DemTong==0){
        std::cout<< "Khong tim thay loai xe\n";
    }

}
void SystemInterface::PhiTrungBinh(){
    std::string LoaiXe[3] = {"Car","Motorcycle","Bicycle"};
    for(int i = 0; i<3;i++){
        int dem = 0;
        double tong = 0;
        for(int j = 0; j < SoLuong_BaiDo; j++){
            int d;
            double s;
            if(baidoxe[j].CoLoai(LoaiXe[i],d,s) && d>0){
                dem+=d;
                tong+=s;
            }
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