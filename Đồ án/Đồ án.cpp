#include <stdio.h>
#include <conio.h>
#include "windows.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#define esp 1e-7
#define MAX 1000
double a[MAX][MAX], x[MAX], b[MAX], v[MAX][MAX];
int vt_dat_an[MAX], check_in_nghiem_tq1, check_in_nghiem_tq2, check_in_nghiem_tq3, check_nghiem_tong_quat, n;
FILE* input, * output;
char nameFile[30];
void swap(double* a, double* b);
double my_fabs(double a);
void gotoXY(int x, int y);
void SetColor(WORD color);
void init();
void In_ma_tran();
void Sapthutu();
void Sapthutu_TH_vo_so_nghiem();
void Khu_Gauss(int n);
void Giai_he();
int kiem_tra_vo_so_nghiem_hang_ngang();
int kiem_tra_vo_so_nghiem_hang_doc();
void tim_nghiem_tong_quat();
void loai_tru_sai_so();
void loai_tru_sai_so_mang_v();
int tinh_so_dong_bang_khong(int n);
void xuat_nghiem_tong_quat();
int main()
{
    int ok = 1;
    int check = 1;
    while (check)
    {
        SetColor(14);
        int x = 43, y = 5;
        gotoXY(x, y);
        printf("PHEP KHU GAUSS");
        x = 31, y = 6;
        gotoXY(x, y);
        printf("NHOM 2: VO PHUOC HOANG VA TRAN DINH MANH");
        x = 24, y = 2;
        char a = 196;
        while (x <= 77)
        {
            gotoXY(x, y);
            if (x == 24)
                printf("%c", 218);
            else if (x == 77)
                printf("%c", 191);
            else
                printf("%c", a);
            x++;
        }
        x = 24, y = 3;
        a = 179;
        while (y <= 9)
        {
            gotoXY(x, y);
            printf("%c", a);
            y++;
        }
        x = 77, y = 3;
        while (y <= 9)
        {
            gotoXY(x, y);
            printf("%c", a);
            y++;
        }
        x = 24, y = 9;
        a = 196;
        while (x <= 77)
        {
            gotoXY(x, y);
            if (x == 24)
                printf("%c", 192);
            else if (x == 77)
                printf("%c", 217);
            else
                printf("%c", a);
            x++;
        }
        printf("\n\nDANH SACH CAC CONG VIEC :\n");
        SetColor(7);
        if (ok == 1)
        {
            SetColor(9);
            printf("1.Tim file va xuat du lieu trong file ra!\n");
            SetColor(7);
        }
        else
            printf("1.Tim file va xuat du lieu trong file ra!\n");
        if (ok == 2)
        {
            SetColor(9);
            printf("2.Dua phuong trinh ve ma tran bac thang!\n");
            SetColor(7);
        }
        else
            printf("2.Dua phuong trinh ve ma tran bac thang!\n");
        if (ok == 3)
        {
            SetColor(9);
            printf("3.In nghiem!\n");
            SetColor(7);
        }
        else
            printf("3.In nghiem!\n");
        if (ok == 4)
        {
            SetColor(9);
            printf("0.Ket thuc chuong trinh!\n");
            SetColor(7);
        }
        else
            printf("0.Ket thuc chuong trinh!\n");
        char kitu = _getch();
        if (kitu == 72)
        {
            if (ok == 1)
                ok = 4;
            else
                ok--;
        }
        else if (kitu == 80)
        {
            if (ok == 4)
                ok = 1;
            else
                ok++;
        }
        else if (kitu == 13)
        {
            switch (ok)
            {
            case 1:
            {
                init();
                check_nghiem_tong_quat = 0;
                getch();
                break;
            }
            case 2:
            {
                if (kiem_tra_vo_so_nghiem_hang_ngang() && kiem_tra_vo_so_nghiem_hang_doc())
                {
                    check_nghiem_tong_quat = 1;
                    tim_nghiem_tong_quat();
                }
                else if (kiem_tra_vo_so_nghiem_hang_doc())
                {
                    check_nghiem_tong_quat = 1;
                    Khu_Gauss(n);
                    loai_tru_sai_so();
                    tim_nghiem_tong_quat();
                }
                else
                {
                    if (kiem_tra_vo_so_nghiem_hang_ngang())
                    {
                        check_nghiem_tong_quat = 1;
                        tim_nghiem_tong_quat();
                    }
                    else
                    {
                        Sapthutu();
                        Khu_Gauss(n);
                        loai_tru_sai_so();
                        if (kiem_tra_vo_so_nghiem_hang_ngang())
                        {
                            check_nghiem_tong_quat = 1;
                            tim_nghiem_tong_quat();
                        }
                    }
                }
                getch();
                break;
            }
            case 3:
            {
                if (check_nghiem_tong_quat)
                {
                    xuat_nghiem_tong_quat();
                }
                else
                {
                    Giai_he();
                }
                getch();
                break;
            }
            case 4:
            {
                check = 0;
                printf("Ket thuc chuong trinh!\n");
                getch();
                break;
            }
            }
        }
        system("cls");
    }
    return 0;
}
void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void gotoXY(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x, y };
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void init()
{
    int check = 1, d = 0;
    do
    {
        printf("\nNhap ten file can tim: ");
        fflush(stdin);
        gets_s(nameFile);
        strcat(nameFile, ".txt");
        if (input = fopen(nameFile, "r"))
        {
            check = 0;
            printf("File ton tai!!\n");
            fscanf(input, "%d", &n);
            if (fgetc(input) != '\n')
            {
                printf("Du lieu khong hop le");
                return;
            }
            for (int i = 0; i < n; ++i)
            {
                double m = 0;
                for (int j = 0; j < n; ++j)
                {
                    if (!feof(input))
                    {
                        fscanf(input, "%lf", &a[i][j]);
                        m += a[i][j];
                    }
                    else
                    {
                        printf("Du lieu khong hop le!\n");
                        return;
                    }
                }
                b[i] = m;
            }
            fclose(input);
            printf("\nPhuong trinh AX = B la : \n");
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    printf("%.3lf\t", a[i][j]);
                }
                printf(" %.3lf", b[i]);
                printf("\n");
            }
        }
        else
        {
            printf("File khong ton tai! Yeu cau nhap lai ten file! \n");
        }
    } while (check);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            v[i][j] = 0;
        }
    }
    check_in_nghiem_tq1 =  check_in_nghiem_tq2 =  check_in_nghiem_tq3 = check_nghiem_tong_quat = 0;

}
void swap(double* a, double* b)
{
    double tmp = *a;
    *a = *b;
    *b = tmp;
}
double my_fabs(double a)
{
    if (a < 0)
        return -a;
    else
        return a;
}
void In_ma_tran()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%15.3lf ", a[i][j]);
        }
        printf("%15.3lf", b[i]);
        printf("\n");
    }
}
void Sapthutu()
{
    for (int i = 0; i < n - 1; i++)
        for (int k = i + 1; k < n; k++)
            if ((my_fabs(a[i][i]) < my_fabs(a[k][i])) || (a[i][i] == 0 && i == 0))
            {
                for (int j = 0; j < n; j++)
                {
                    swap(&a[i][j], &a[k][j]);
                }
                swap(&b[i], &b[k]);
            }
}
void Sapthutu_TH_vo_so_nghiem()
{
    for (int i = n - 1; i >= 0; i--)
    {
        int ch = 0;
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] != 0)
            {
                ch = 1;
                break;
            }
        }
        if (ch)
        {
            for (int k = 0; k < i; k++)
            {
                int ch2 = 1;
                for (int l = 0; l < n; l++)
                {
                    if (a[k][l] != 0)
                        ch2 = 0;
                }
                if (ch2)
                {
                    for (int q = 0; q < n; q++)
                    {
                        swap(&a[i][q], &a[k][q]);
                    }
                    swap(&b[i], &b[k]);
                }
            }
        }
    }
}
int kiem_tra_dk_dac_biet_trong_khu_gauss(int i, int c, int kt)
{
    for (int k = i; k < kt; k++)
    {
        if (a[k][c] != 0)
            return 0;
    }
    return 1;
    /*
    * 2 3 4 5
    * 0 0 2 3
    * 0 0 0 4
    * 0 0 0 5
    */
}
void loai_tru_sai_so()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (my_fabs(a[i][j]) < esp)
                a[i][j] = 0;
        }
        if (my_fabs(b[i]) < esp)
            b[i] = 0;
    }
}
void loai_tru_sai_so_mang_v()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (my_fabs(v[i][j]) < esp)
                v[i][j] = 0;
        }
    }
}
int tinh_so_dong_bang_khong(int n)
{
    int kt = n - 1;
    int check = 1;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] != 0)
                check = 0;
        }
        if (check == 0)
            break;
        kt--;
    }
    return n - 1 - kt; 
}
void Khu_Gauss(int n)
{
    int d = 1;
    int z, p;
    p = tinh_so_dong_bang_khong(n);
    z = n - 1 - p;
    for (int i = 0; i < z; i++)
    {
        int c = i;
        int check = 1;
        while (kiem_tra_dk_dac_biet_trong_khu_gauss(i, c, z + 1))
        {
            if (c == n - 1)
            {
                /*1 2 3 4
                  3 1 3 1 
                  0 0 0 0
                  0 0 0 0
                */
                if (a[i][c] == 0)
                {
                    check = 0;
                }
                break;
            }
            ++c;
        }
        if (check)
        {
            for (int k = i + 1; k < z + 1; k++)
            {
                if (a[i][c] == 0)
                {
                    for (int j = 0; j < n; j++)
                    {
                        swap(&a[i][j], &a[k][j]);
                    }
                    swap(&b[i], &b[k]);
                }
                double m = a[k][c] * 1.0 / a[i][c];
                for (int j = 0; j < n; j++)
                    a[k][j] = a[k][j] - m * a[i][j];
                b[k] = b[k] - m * b[i];
            }
        }
        printf("Lan khu thu %d\n", d);
        In_ma_tran();
        printf("\n");
        d++;
        loai_tru_sai_so();
    }
}
void Giai_he()
{
    output = fopen("DATA.OUT.txt", "w");
    fprintf(output, "%s", "Nghiem cua phuong trinh la:\n");
    for (int i = n - 1; i >= 0; i--)
    {
        x[i] = b[i];
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                x[i] = x[i] - a[i][j] * x[j];
            }
        }
        x[i] = x[i] * 1.0 / a[i][i];
    }
    printf("Nghiem cua phuong trinh la:\n");
    for (int i = 0; i < n; i++)
    {
        printf("x%d = %.2lf\n", i + 1, x[i]);
        fprintf(output, "x%d = %.2lf\n", i + 1, x[i]);
    }
    fclose(output);
}
int kiem_tra_vo_so_nghiem_hang_ngang()
{
    for (int i = n - 1; i >= 0; i--)
    {
        int ktra = 1;
        for (int j = 0; j < n; j++)
            if (a[i][j] != 0)
                ktra = 0;
        if (ktra)
            return 1;
    }
    return 0;
}
int kiem_tra_vo_so_nghiem_hang_doc()
{
    for (int j = 0; j < n; j++)
    {
        int ktra = 1;
        for (int i = 0; i < n; i++)
            if (a[i][j] != 0)
                ktra = 0;
        if (ktra)
            return 1;
    }
    return 0;
}
int kiem_tra_TH_VSN_co_nghiem_cuoi_bang_1(int kt)
{
    for (int i = kt; i >= 0; i--)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] == 0)
                continue;
            if (a[i][j] != 0 && j == n - 1)
                return 1;
            else
                break;
        }
    }
    return 0;
}

void tim_nghiem_tong_quat()
{
    int gd[1000];
    for (int i = 0; i < n; i++)
    {
        gd[i] = 0;
    }
    int kt = n - 1;
    Sapthutu_TH_vo_so_nghiem();
    kt = n - 1 - tinh_so_dong_bang_khong(n);
    for (int i = 0; i <= kt; i++)
        for (int k = i + 1; k <= kt; k++)
            if ((my_fabs(a[i][i]) < my_fabs(a[k][i])) || (a[i][i] == 0 && i == 0))
            {
                for (int j = 0; j < n; j++)
                {
                    swap(&a[i][j], &a[k][j]);
                }
                swap(&b[i], &b[k]);
            }
    Khu_Gauss(n);
    loai_tru_sai_so();//tranh viec sai so khong dang co
    kt = n - 1;
    kt -= tinh_so_dong_bang_khong(n);
    for (int i = 0; i < n; i++)
        vt_dat_an[i] = 0;
    int hk = 0;
    int check1 = 1;
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (a[i][j] != 0)
                check1 = 0;
        }
        if (check1)
        {
            hk++;
            vt_dat_an[j] = 1;
        }
        check1 = 1;
    }
    if (a[0][0] == 0 && n - 1 - kt - hk == 0)
    {
        check_in_nghiem_tq1 = 1;
    }
    else if (a[0][0] == 0 && n - 1 - kt - hk > 0)
    {
        check_in_nghiem_tq2 = 1;
        for (int i = n - 1; i > kt + hk; i--)
        {
            v[i][n - i] = 1;
            vt_dat_an[i] = 1;
        }
        for (int i = 1; i < n; i++)
        {
            if (vt_dat_an[i])
                v[i][n - i] = 1;
        }
        int cong_don = 0;
        for (int i = kt + hk; i >= 1; i--)
        {
            if (!vt_dat_an[i])
            {
                double he_so_khu = 0;
                for (int p = 0; p < n; p++)
                {
                    if (a[i - hk + cong_don][p] != 0)
                    {
                        he_so_khu = a[i - hk + cong_don][p];
                        break;
                    }
                }
                for (int j = 0; j < n; j++)
                {
                    if (j == 0)
                    {
                        v[i][j] += b[i - hk + cong_don] * 1.0 / he_so_khu;
                        for (int k = i + 1; k < n; k++)
                        {
                            v[i][j] -= (a[i - hk + cong_don][k] * 1.0 / he_so_khu) * v[k][j];
                        }
                    }
                    else
                    {
                        for (int k = i + 1; k < n; k++)
                        {
                            v[i][j] -= (a[i - hk + cong_don][k] * 1.0 / he_so_khu) * v[k][j];
                        }
                    }
                }
            }
            else
                cong_don++;
        }
        loai_tru_sai_so_mang_v();
    }
    else
    {
        if (kiem_tra_TH_VSN_co_nghiem_cuoi_bang_1(kt))
        {
            int so_luong = n - 1 - kt;
            int c = 0, z = 0;
            for (int i = 0; i <= kt; i++)
            {
                if (z == so_luong)
                    break;
                if (a[i][c] == 0)
                {
                    v[i][n - c] = 1;
                    gd[c] = 1;
                    c++;
                    z++;
                }
                c++;
            }
            int tc = n - 1;
            while (!gd[tc])
            {
                v[tc][0] = 1;
                tc--;
            }
            for (int i = kt; i >= 0; i--)
            {
                if (gd[i])
                    continue;
                else
                {
                    double he_so_khu = 0;
                    for (int p = 0; p < n; p++)
                    {
                        if (a[i][p] != 0)
                        {
                            he_so_khu = a[i][p];
                            break;
                        }
                    }
                    for (int j = 0; j < n; j++)
                    {
                        if (j == 0)
                        {
                            v[i][j] += b[i] * 1.0 / he_so_khu;
                            for (int k = i + 1; k < n; k++)
                            {
                                v[i][j] -= (a[i][k] * 1.0 / he_so_khu) * v[k][j];
                            }
                        }
                        else
                        {
                            for (int k = i + 1; k < n; k++)
                            {
                                v[i][j] -= (a[i][k] * 1.0 / he_so_khu) * v[k][j];
                            }
                        }
                    }
                }
            }
        }
        else
        {
            int so_luong = n - kt - 1;
            int c = 0, z = 0;
            int ktra = 0;
            for (int i = 0; i <= kt; i++)
            {
                if (a[i][i] == 0)
                {
                    ktra = 1;
                    break;
                }
            }
            if (ktra)
            {
                for (int i = 0; i <= kt; i++)
                {
                    if (z == so_luong)
                        break;
                    if (a[i][c] == 0)
                    {
                        v[i][n - c] = 1;
                        gd[c] = 1;
                        c++;
                        z++;
                    }
                    c++;
                }
                v[n - 1][1] = 1;
                for (int i = kt; i >= 0; i--)
                {
                    if (gd[i])
                    {
                        double he_so_khu = 0;
                        for (int p = 0; p < n; p++)
                        {
                            if (a[i][p] != 0)
                            {
                                he_so_khu = a[i][p];
                                break;
                            }
                        }
                        for (int j = 0; j < n; j++)
                        {
                            if (j == 0)
                            {
                                v[i + 1][j] += b[i] * 1.0 / he_so_khu;
                                for (int k = i + 1; k < n; k++)
                                {
                                    v[k][j] -= (a[i][k] * 1.0 / he_so_khu) * v[k + 1][j];
                                }
                            }
                            else
                            {
                                for (int k = i + 1; k < n; k++)
                                {
                                    v[k][j] -= (a[i][k + 1] * 1.0 / he_so_khu) * v[k + 1][j];
                                }
                            }
                        }
                    }
                    else
                    {
                        double he_so_khu = 0;
                        for (int p = 0; p < n; p++)
                        {
                            if (a[i][p] != 0)
                            {
                                he_so_khu = a[i][p];
                                break;
                            }
                        }
                        for (int j = 0; j < n; j++)
                        {
                            if (j == 0)
                            {
                                v[i][j] += b[i] / he_so_khu;
                                for (int k = i + 1; k < n; k++)
                                {
                                    v[i][j] -= (a[i][k] * 1.0 / he_so_khu) * v[k][j];
                                }
                            }
                            else
                            {
                                for (int k = i + 1; k < n; k++)
                                {
                                    v[i][j] -= (a[i][k] * 1.0 / he_so_khu) * v[k][j];
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                for (int i = n - 1; i > kt; i--)
                {
                    v[i][n - i] = 1;
                }
                for (int i = kt; i >= 0; i--)
                {
                    double he_so_khu = 0;
                    for (int p = 0; p < n; p++)
                    {
                        if (a[i][p] != 0)
                        {
                            he_so_khu = a[i][p];
                            break;
                        }
                    }
                    for (int j = 0; j < n; j++)
                    {
                        if (j == 0)
                        {
                            v[i][j] += b[i] * 1.0 / he_so_khu;
                            for (int k = i + 1; k < n; k++)
                            {
                                v[i][j] -= (a[i][k] * 1.0 / he_so_khu) * v[k][j];
                            }
                        }
                        else
                        {
                            for (int k = i + 1; k < n; k++)
                            {
                                v[i][j] -= (a[i][k] * 1.0 / he_so_khu) * v[k][j];
                            }
                        }
                    }
                }
            }
        }
        loai_tru_sai_so_mang_v();
        check_in_nghiem_tq3 = 1;
    }
}
void xuat_nghiem_tong_quat()
{
    output = fopen("DATA.OUT.txt", "w");
    if (check_in_nghiem_tq1)
    {
        printf("Nghiem cua he phuong trinh la:\n");
        printf("x1 = x1\n");
        fprintf(output, "%s", "Nghiem cua he phuong trinh la:\n");
        fprintf(output, "%s", "x1 = x1\n");
        for (int i = 1; i < n; i++)
        {
            if (vt_dat_an[i])
            {
                printf("x%d = x%d\n", i + 1, i + 1);
                fprintf(output, "x%d = x%d\n", i + 1, i + 1);
            }
            else
            {
                printf("x%d = 1\n", i + 1);
                fprintf(output, "x%d = 1\n", i + 1);
            }
        }
    }
    else if (check_in_nghiem_tq2)
    {
        printf("Nghiem tong quat la:\n");
        printf("x1 = 1.00x1");
        fprintf(output, "Nghiem tong quat la:\n");
        fprintf(output, "%s", "x1 = 1.00x1");
        for (int i = 1; i < n; i++)
        {
            printf("\nx%d = ", i + 1);
            fprintf(output, "\nx%d = ", i + 1);
            int check1 = 1;
            for (int j = 0; j < n; j++)
            {
                if (v[i][j] != 0)
                {
                    if (j == 0)
                    {
                        printf(" %.2lf ", v[i][j]);
                        fprintf(output, " %.2lf", v[i][j]);
                    }
                    else
                    {
                        if (v[i][0] == 0 && check1)
                        {
                            printf(" %.2lfx%d", v[i][j], n - j + 1);
                            fprintf(output, " %.2lfx%d", v[i][j], n - j + 1);
                            check1 = 0;
                        }
                        else
                        {
                            if (v[i][j] > 0)
                            {
                                printf("+ %.2lfx%d", v[i][j], n - j + 1);
                                fprintf(output, "+ %.2lfx%d", v[i][j], n - j + 1);
                            }
                            else
                            {
                                printf(" %.2lfx%d", v[i][j], n - j + 1);
                                fprintf(output, " %.2lfx%d", v[i][j], n - j + 1);
                            }
                        }
                    }
                }
            }
        }
    }
    else if (check_in_nghiem_tq3)
    {
        printf("Nghiem cua he phuong trinh la:\n");
        fprintf(output, "%s\n", "Nghiem cua he phuong trinh la:");
        for (int i = 0; i < n; i++)
        {
            printf("\nx%d = ", i + 1);
            fprintf(output, "\nx%d = ", i + 1);
            int check1 = 1;
            for (int j = 0; j < n; j++)
            {
                if (v[i][j] != 0)
                {
                    if (j == 0)
                    {
                        printf("%.2lf", v[i][j]);
                        fprintf(output, "%.2lf", v[i][j]);
                    }
                    else
                    {
                        if (v[i][0] == 0 && check1)
                        {
                            printf("%.2lfx%d", v[i][j], n - j + 1);
                            fprintf(output, "%.2lfx%d", v[i][j], n - j + 1);
                            check1 = 0;
                        }
                        else
                        {
                            if (v[i][j] > 0)
                            {
                                printf(" + %.2lfx%d", v[i][j], n - j + 1);
                                fprintf(output, " + %.2lfx%d", v[i][j], n - j + 1);
                            }
                            else
                            {
                                printf(" %.2lfx%d", v[i][j], n - j + 1);
                                fprintf(output, " %.2lfx%d", v[i][j], n - j + 1);
                            }
                        }
                    }
                }
            }
        }
    }
    fclose(output);
}