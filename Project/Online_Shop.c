#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cJSON.h"

char *randstring(int length) {
    static int mySeed = 25011984;
    char *string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t stringLen = strlen(string);
    char *randomString = NULL;
    srand(time(NULL) * length + ++mySeed);
    if (length < 1) {
        length = 1;
    }
    randomString = malloc(sizeof(char) * (length + 1));
    if (randomString) {
        short key;
        for (int n = 0; n < length; n++) {
            key = rand() % stringLen;
            randomString[n] = string[key];
        }
        randomString[length] = '\0';
        return randomString;
    } else {
        printf("No memory");
        exit(1);
    }
}

int main() {
    int wallet;
    char num[1], sec_num[1], sec_question1[50], sec_question2[50];
    FILE *ptr, *User_List, *category_LIST, *Ban, *Unban, *pro, *help;
    start:
    printf("Welcome To Soheil Food Court\n");
    printf("1.Sign Up\n2.Login\n3.Exit\n");
    printf("In Order To Help You Please Enter Your Willing Options Number\n");
    gets(num);
    system("cls");
    if (num[0] == '1') {
        char username[25], password[16], firstname[15], lastname[15];
        char *string;
        cJSON *user;
        printf("Please Enter Your Username (It Should Be At Last 20 Characters)\nEnter 0 If You Want To Go To Starting Page\n");
        use:
        gets(username);
        if (username[0] == '0') {
            system("cls");
            goto start;
        }
        char copy_NAME[100];
        strcpy(copy_NAME, username);
        strcat(copy_NAME, "\t");
        strcat(username, ".json");
        ptr = fopen(username, "r");
        if (ptr != 0) {
            fclose(ptr);
            printf("This Username Is Already Chosen.\n Please Choose Another One\n");
            goto use;
        }
        printf("\nPlease Enter Your Password (It Should Be At Last 16 Characters)\nEnter 0 If You Want To Go To Starting Page\n");
        gets(password);
        if (password[0] == '0') {
            system("cls");
            goto start;
        }
        user = cJSON_CreateObject();
        cJSON_AddStringToObject(user, "password", password);
        system("cls");
        printf("For Your Own Security Please Answer Two Following Questions.\n\n");
        printf("What's Your Favorite National Soccer Team?\nEnter 0 If You Want To Go To Starting Page\n");
        gets(sec_question1);
        if (sec_question1[0] == '0') {
            system("cls");
            goto start;
        }
        printf("What's Your Favorite Movie/Series Of All Time?\nEnter 0 If You Want To Go To Starting Page\n");
        gets(sec_question2);
        if (sec_question2[0] == '0') {
            system("cls");
            goto start;
        }
        cJSON_AddStringToObject(user, "first_question", sec_question1);
        cJSON_AddStringToObject(user, "second_question", sec_question2);
        system("cls");
        printf("\nPlease Enter Your First Name (It Should Be At Last 15 Characters)\nEnter 0 If You Want To Go To Starting Page\n");
        gets(firstname);
        if (firstname[0] == '0') {
            system("cls");
            goto start;
        }
        cJSON_AddStringToObject(user, "firstname", firstname);
        printf("\nPlease Enter Your Last Name (It Should Be At Last 15 Characters)\nEnter 0 If You Want To Go To Starting Page\n");
        gets(lastname);
        if (lastname[0] == '0') {
            system("cls");
            goto start;
        }
        cJSON_AddStringToObject(user, "lastname", lastname);
        system("cls");
        printf("Please Choose Your Role By Importing The Specified Number\nEnter 0 If You Want To Go To Starting Page\n");
        printf("1.Customer\n2.Retailer\n3.Admin\n");
        gets(sec_num);
        char *role;
        if (sec_num[0] == '0') {
            system("cls");
            goto start;
        }
        if (sec_num[0] == '1') role = "Customer";
        if (sec_num[0] == '2') role = "Retailer";
        if (sec_num[0] == '3') role = "Admin";
        cJSON_AddStringToObject(user, "role", sec_num);
        printf("\nPlease Enter Your Starting Money (In Dollars)\n");
        scanf("%d%*c", &wallet);
        cJSON_AddNumberToObject(user, "money", wallet);
        cJSON_AddStringToObject(user, "Situation", "");
        cJSON_AddNumberToObject(user, "successful_purchases", 0);
        cJSON_AddNumberToObject(user, "points", 0);
        cJSON_AddStringToObject(user, "discount_code", "empty");
        string = cJSON_Print(user);
        ptr = fopen(username, "w");
        fputs(string, ptr);
        fclose(ptr);
        User_List = fopen("List_of_USERS.json", "a");
        if (User_List == 0) {
            fclose(User_List);
            User_List = fopen("List_of_USERS.json", "w");
        }
        fputs(copy_NAME, User_List);
        fputs("\t", User_List);
        fputs(role, User_List);
        fputs("\n", User_List);
        fclose(User_List);
        system("cls");
        printf("\nYour Account Has Been Successfully Created\n\n");
        goto start;
    }
    if (num[0] == '2') {
        char username[50], password[80], new_pass[80], user_copy[50], question1[60], question2[60];
        char *notebook;
        int non;
        printf("Please Enter Your Username\n");
        gets(username);
        strcpy(user_copy, username);
        strcat(username, ".json");
        ptr = fopen(username, "r+");
        if (ptr == 0) {
            fclose(ptr);
            printf("Invalid Username.\nYou Will Be Redirected To First Menu\n");
            goto start;
        }
        char user[200];
        fread(user, 1, 1000, ptr);
        cJSON *info_as_json = cJSON_Parse(user);
        cJSON *password_as_json = cJSON_GetObjectItem(info_as_json, "password");
        cJSON *role_as_json = cJSON_GetObjectItem(info_as_json, "role");
        cJSON *firstname_as_json = cJSON_GetObjectItem(info_as_json, "firstname");
        cJSON *lastname_as_json = cJSON_GetObjectItem(info_as_json, "lastname");
        cJSON *money_as_json = cJSON_GetObjectItem(info_as_json, "money");
        cJSON *situation_as_json = cJSON_GetObjectItem(info_as_json, "Situation");
        cJSON *ques1_as_json = cJSON_GetObjectItem(info_as_json, "first_question");
        cJSON *ques2_as_json = cJSON_GetObjectItem(info_as_json, "second_question");
        if (cJSON_GetStringValue(situation_as_json) != NULL) {
            if (strcmp(cJSON_GetStringValue(situation_as_json), "Banned") == 0) {
                printf("Unfortunately You Are Banned By Admin!\nYou Will Be Redirected To First Menu.\n\n");
                fclose(ptr);
                goto start;
            }
        }
        printf("If You Have Forgotten Your Password Please Enter 6.\nIf Not Enter Any Other Number exp:5\n");
        scanf("%d%*c", &non);
        if (non == 6) {
            system("cls");
            printf("In Order To Proceed Answer Two Following Questions.\n\n");
            printf("What's Your Favorite National Soccer Team?\n");
            gets(question1);
            printf("What's Your Favorite Movie Of All Time?\n");
            gets(question2);
            if (strcmp(cJSON_GetStringValue(ques1_as_json), question1) == 0 &&
                strcmp(cJSON_GetStringValue(ques2_as_json), question2) == 0) {
                system("cls");
                printf("Enter Your New Password:)\n");
                gets(new_pass);
                cJSON_ReplaceItemInObject(info_as_json, "password", cJSON_CreateString(new_pass));
                notebook = cJSON_Print(info_as_json);
                fclose(ptr);
                ptr = fopen(username, "w");
                fputs(notebook, ptr);
                fclose(ptr);
                system("cls");
                printf("You Have Successfully Changed Your Password:)\n\n");
                goto start;
            } else {
                fclose(ptr);
                system("cls");
                printf("Your Answers Were Wrong:(\nYou'll Be Redirected To First Menu.\n\n");
                goto start;
            }
        }
        printf("\nPlease Enter Your Password\n");
        gets(password);
        fclose(ptr);
        if (strcmp(cJSON_GetStringValue(password_as_json), password) != 0) {
            printf(" The Password Doesn't Match With The Username.\nYou Will Be Redirected To First Menu\n\n");
            goto start;
        } else {
            printf("\nYou Have Successfully Logged In\n");
            if (strcmp(cJSON_GetStringValue(role_as_json), "1") == 0) {
                account:
                printf("\nHi %s %s\n\n", cJSON_GetStringValue(firstname_as_json),
                       cJSON_GetStringValue(lastname_as_json));
                printf("What Do You Want To Do Today?\n");
                printf("Enter Your Willing Options Number\n1.Your Account\n2.Our Products\n3.Orders History\n4.Discount Code\n5.Add Comment\n\n");
                printf("For Logging Out Enter 0\n");
                int numb;
                scanf("%d%*c", &numb);
                system("cls");
                if (numb == 1) {
                    char copy_id[300];
                    int a;
                    help = fopen(username, "r");
                    fread(copy_id, 1, 1000, help);
                    cJSON *id_as_js = cJSON_Parse(copy_id);
                    cJSON *cash_as_js = cJSON_GetObjectItem(id_as_js, "money");
                    cJSON *num_purchases = cJSON_GetObjectItem(id_as_js, "successful_purchases");
                    fclose(help);
                    printf("Username: %s\n", user_copy);
                    printf("Firstname: %s\n", cJSON_GetStringValue(firstname_as_json));
                    printf("Lastname: %s\n", cJSON_GetStringValue(lastname_as_json));
                    printf("Cash In Hand: %g\n", cJSON_GetNumberValue(cash_as_js));
                    printf("Number of Successful Purchases:%g\n", cJSON_GetNumberValue(num_purchases));
                    printf("\nFor Going Back Please Enter 0\n");
                    scanf("%d%*c", &a);
                    goto account;
                }
                if (numb == 2) {
                    buy:
                    pro = fopen("Product_LIST_manufactured.json", "r");
                    double decrease;
                    decrease = 0.00;
                    char c;
                    if (pro == 0) {
                        printf("There Isn't Any Available Product At This Moment:(\n Please Try Again Later.\n");
                        goto account;
                    }
                    c = fgetc(pro);
                    printf("Available Products Are:\n\n");
                    while (c != EOF) {
                        printf("%c", c);
                        c = fgetc(pro);
                    }
                    fclose(pro);
                    printf("If You Want To Check The Sales Before Buying, Enter 6\nIf Not, Enter Any Other One Digit Number(LIKE 5).\n");
                    int gu;
                    scanf("%d%*c", &gu);
                    if (gu == 6) {
                        discount:
                        printf("Enter The Exact Name of The Product.\nFor Going Back To Account Enter 0\n\n");
                        char string_name[60], copy[60];
                        char read_inf[300];
                        int p;
                        gets(string_name);
                        strcpy(copy, string_name);
                        strcat(string_name, "_Product.json");
                        help = fopen(string_name, "r");
                        if (help == 0) {
                            fclose(help);
                            printf("Undefined Product! Try Again\n");
                            goto discount;
                        }
                        fread(read_inf, 1, 1000, help);
                        cJSON *info = cJSON_Parse(read_inf);
                        cJSON *sale = cJSON_GetObjectItem(info, "percent_sale");
                        printf("The %s Is on %g Percent Sale Today:)\n\n", copy, cJSON_GetNumberValue(sale));
                        fclose(help);
                        printf("Enter 6 To Check Another On Sale Product(Back to menu).\nEnter Any Other One Digit Number To Proceed To Buying;\n\n");
                        scanf("%d%*c", &p);
                        if (p == 6) {
                            system("cls");
                            goto buy;
                        }
                        system("cls");
                    }
                    printf("Have A Discount Code? If You Want To Use It Enter 8. If Not, Enter Any Other One Digit Number(LIKE 5).\n");
                    int as;
                    scanf("%d%*c", &as);
                    if (as == 8) {
                        printf("Enter Your 10 digit code Carefully.\n");
                        char the_read[500], code[11];
                        char *a_print;
                        gets(code);
                        help = fopen(username, "r+");
                        fread(the_read, 1, 1000, help);
                        cJSON *good_info_js = cJSON_Parse(the_read);
                        cJSON *code_baz = cJSON_GetObjectItem(good_info_js, "discount_code");
                        if (strcmp(cJSON_GetStringValue(code_baz), code) == 0) {
                            system("cls");
                            printf("Bar Tabl Shadaneh Bekoob:)\n");
                            if (cJSON_GetStringValue(code_baz)[0] == '1' && cJSON_GetStringValue(code_baz)[1] == '1') {
                                decrease = 0.1;
                                printf("You Have 10 percent Discount Exclusively\n");
                            }
                            if (cJSON_GetStringValue(code_baz)[0] == '2' && cJSON_GetStringValue(code_baz)[1] == '2') {
                                decrease = 0.25;
                                printf("You Have 25 percent Discount Exclusively\n");
                            }
                            if (cJSON_GetStringValue(code_baz)[0] == '3' && cJSON_GetStringValue(code_baz)[1] == '3') {
                                decrease = 0.5;
                                printf("You Have 50 percent Discount Exclusively\n");
                            }
                            cJSON_ReplaceItemInObject(good_info_js, "discount_code", cJSON_CreateString("empty"));
                            a_print = cJSON_Print(good_info_js);
                            fclose(help);
                            help = fopen(username, "w");
                            fputs(a_print, help);
                            fclose(help);
                        } else {
                            fclose(help);
                            system("cls");
                            printf("Invalid Code:( Try Again.\n");
                            goto buy;
                        }
                    }
                    char more_cpy[60];
                    printf("If You Want to Check Comments Aboout A Product Enter 7.If not Enter Any Other One Digit Number(like 5)\n");
                    int kam;
                    scanf("%d%*c", &kam);
                    if (kam == 7) {
                        system("cls");
                        printf("Enter The Name Of The Willing Product.\n");
                        gets(more_cpy);
                        strcat(more_cpy, "_comList.json");
                        pro = fopen(more_cpy, "r");
                        if (pro == 0) {
                            fclose(pro);
                            system("cls");
                            printf("There Isn't Any Comment About This Product Or This Product Isn't Defined.\nBack To Account.\n\n");
                            goto account;
                        }
                        char y;
                        y = fgetc(pro);
                        printf("Available Comments Are:\n");
                        while (y != EOF) {
                            printf("%c", y);
                            y = fgetc(pro);
                        }
                        fclose(pro);
                    }
                    printf("\nEnter The Exact Name of The Product Your Willing To Buy.\nFor Going Back Enter 0\n\n");
                    char name_product[50], cop_name_pro[60];
                    gets(name_product);
                    strcpy(cop_name_pro, name_product);
                    if (name_product[0] == '0') {
                        system("cls");
                        goto account;
                    }

                    strcat(name_product, "_Product.json");
                    pro = fopen(name_product, "r");
                    if (pro == 0) {
                        fclose(pro);
                        system("cls");
                        printf("Invalid Product! Please Pay Attention To The Names.\nTry Again\n\n");
                        goto buy;
                    }
                    fclose(pro);
                    int how_many;
                    printf("How Many of This Product Do You Want?\n\n");
                    scanf("%d%*c", &how_many);
                    char read_info[400], user_info[400];
                    pro = fopen(name_product, "r+");
                    help = fopen(username, "r+");
                    fread(read_info, 1, 1000, pro);
                    fread(user_info, 1, 1000, help);
                    cJSON *info_as_js = cJSON_Parse(read_info);
                    cJSON *price_as_js = cJSON_GetObjectItem(info_as_js, "price");
                    cJSON *existing_num_as_js = cJSON_GetObjectItem(info_as_js, "inventory");
                    cJSON *retailer_inf_as_js = cJSON_GetObjectItem(info_as_js, "retailer_name");
                    cJSON *sale_as_js = cJSON_GetObjectItem(info_as_js, "percent_sale");
                    if (how_many > cJSON_GetNumberValue(existing_num_as_js)) {
                        fclose(help);
                        fclose(pro);
                        system("cls");
                        printf("My Apologies:( We Don't Have Enough of This Product.\nTry Again\n\n");
                        goto buy;
                    }
                    cJSON *user_info_as_js = cJSON_Parse(user_info);
                    cJSON *cash_as_js = cJSON_GetObjectItem(user_info_as_js, "money");
                    if (cJSON_GetNumberValue(cash_as_js) <
                        (1.0 - (cJSON_GetNumberValue(sale_as_js) / 100.0) - decrease) *
                        cJSON_GetNumberValue(price_as_js) * how_many) {
                        fclose(help);
                        fclose(pro);
                        system("cls");
                        printf("Sorry:( Seems Like You Don't Have Enough Cash!\nTry Another Time\n\n");
                        goto buy;
                    }
                    char *user_edited;
                    char *product_edited;
                    cJSON *num_success_buy = cJSON_GetObjectItem(user_info_as_js, "successful_purchases");
                    cJSON *points_as_js = cJSON_GetObjectItem(user_info_as_js, "points");
                    cJSON_ReplaceItemInObject(info_as_js, "inventory",
                                              cJSON_CreateNumber(cJSON_GetNumberValue(existing_num_as_js) - how_many));
                    cJSON_ReplaceItemInObject(user_info_as_js, "money", cJSON_CreateNumber(
                            cJSON_GetNumberValue(cash_as_js) -
                            ((1.0 - (cJSON_GetNumberValue(sale_as_js) / 100.0) - decrease) *
                             cJSON_GetNumberValue(price_as_js) *
                             how_many)));
                    cJSON_ReplaceItemInObject(user_info_as_js, "successful_purchases",
                                              cJSON_CreateNumber(cJSON_GetNumberValue(num_success_buy) + 1));
                    cJSON_ReplaceItemInObject(user_info_as_js, "points",
                                              cJSON_CreateNumber(cJSON_GetNumberValue(points_as_js) + 10));
                    user_edited = cJSON_Print(user_info_as_js);
                    product_edited = cJSON_Print(info_as_js);
                    fclose(pro);
                    fclose(help);
                    help = fopen(username, "w");
                    fputs(user_edited, help);
                    fclose(help);
                    //in ghesmat daram list sell build mikonam
                    pro = fopen(name_product, "w");
                    fputs(product_edited, pro);
                    fclose(pro);
                    pro = fopen("purchases_good.json", "a");
                    if (pro == 0) {
                        fclose(pro);
                        pro = fopen("purchases_good.json", "w");
                    }
                    fputs(user_copy, pro);
                    fprintf(pro, "\n%s\tTotal Price:%g\tNumber of Purchased Item:%d\n", cop_name_pro,
                            ((1.0 - (cJSON_GetNumberValue(sale_as_js) / 100.0)) * cJSON_GetNumberValue(price_as_js) *
                             how_many), how_many);
                    fclose(pro);
                    //az inja ta comment baad daram tarikhche misazam
                    char sec_copy_username[60];
                    strcpy(sec_copy_username, user_copy);
                    strcat(sec_copy_username, "_history_b.json");
                    help = fopen(sec_copy_username, "a");
                    if (help == 0) {
                        fclose(help);
                        help = fopen(sec_copy_username, "w");
                    }
                    fputs(cop_name_pro, help);
                    fprintf(help, "\nTotal Prize:%g\tNumber of Purchased Item:%d\n",
                            ((1.0 - (cJSON_GetNumberValue(sale_as_js) / 100.0) - decrease) *
                             cJSON_GetNumberValue(price_as_js) *
                             how_many), how_many);
                    fclose(help);
                    pro = fopen("Product_LIST_manufactured.json", "a");
                    fprintf(pro, "Note:%d %s Have Been Sold Recently.\n", how_many, cop_name_pro);
                    fclose(pro);
                    //az inja ta akhar daram poolo mirizam hesab seller
                    char retail[60], retail_read[400];
                    char *copy_retail;
                    strcpy(retail, cJSON_GetStringValue(retailer_inf_as_js));
                    strcat(retail, ".json");
                    help = fopen(retail, "r+");
                    fread(retail_read, 1, 1000, help);
                    cJSON *retailing_inf = cJSON_Parse(retail_read);
                    cJSON *cash_retailer = cJSON_GetObjectItem(retailing_inf, "money");
                    cJSON_ReplaceItemInObject(retailing_inf, "money", cJSON_CreateNumber(
                            cJSON_GetNumberValue(cash_retailer) +
                            ((1.0 - (cJSON_GetNumberValue(sale_as_js) / 100.0)) * cJSON_GetNumberValue(price_as_js) *
                             how_many)));
                    copy_retail = cJSON_Print(retailing_inf);
                    fclose(help);
                    help = fopen(retail, "w");
                    fputs(copy_retail, help);
                    fclose(help);
                    decrease = 0.00;
                    // edame baraye comment
                    char idont[100];
                    strcpy(idont, cop_name_pro);
                    strcat(idont, "_");
                    strcat(idont, user_copy);
                    strcat(idont, "_com.json");
                    help = fopen(idont, "r");
                    if (help == 0) {
                        char *agha;
                        fclose(help);
                        help = fopen(idont, "w");
                        cJSON *obj;
                        obj = cJSON_CreateObject();
                        cJSON_AddStringToObject(obj, "comment", "agha");
                        agha = cJSON_Print(obj);
                        fputs(agha, help);
                        fclose(help);
                    } else {
                        fclose(help);
                    }
                    system("cls");
                    printf("Your Order Has Been Successfully Done:)\n\n");
                    goto account;
                }
                if (numb == 3) {
                    char second_copy_user[60];
                    char c;
                    strcpy(second_copy_user, user_copy);
                    strcat(second_copy_user, "_history_b.json");
                    pro = fopen(second_copy_user, "r");
                    if (pro == 0) {
                        fclose(pro);
                        printf("You Haven't Bought Anything Yet:(\nTry Buying First.\n\n");
                        goto account;
                    }
                    c = fgetc(pro);
                    printf("Your Shopping History IS:\n\n");
                    while (c != EOF) {
                        printf("%c", c);
                        c = fgetc(pro);
                    }
                    printf("For Going Back Please Enter 0\n\n");
                    int v;
                    scanf("%d%*c", &v);
                    system("cls");
                    goto account;
                }
                if (numb == 4) {
                    printf("There Are 3 Options For Discount Code Based On Your points\n1.100pts->10percent  2.200pts->25percent  3.300pts->50percent\n");
                    printf("Enter The Number You Demand Or Enter 0 For Going Back To Account.\n");
                    int f;
                    char get_info[500];
                    char *print_inf;
                    scanf("%d%*c", &f);
                    help = fopen(username, "r+");
                    fread(get_info, 1, 1000, help);
                    cJSON *info_as_js = cJSON_Parse(get_info);
                    cJSON *point_as_js = cJSON_GetObjectItem(info_as_js, "points");
                    if (f == 1) {
                        if (cJSON_GetNumberValue(point_as_js) >= 100) {
                            char code_takhfif[11];
                            char *dummy;
                            code_takhfif[0] = '1';
                            code_takhfif[1] = '1';
                            dummy = randstring(8);
                            strcat(code_takhfif, dummy);
                            cJSON_ReplaceItemInObject(info_as_js, "discount_code", cJSON_CreateString(code_takhfif));
                            cJSON_ReplaceItemInObject(info_as_js, "points",
                                                      cJSON_CreateNumber(cJSON_GetNumberValue(point_as_js) - 100));
                            print_inf = cJSON_Print(info_as_js);
                            fclose(help);
                            help = fopen(username, "w");
                            fputs(print_inf, help);
                            fclose(help);
                            system("cls");
                            printf("Congrats:) Now You Have A 10percent Discount Code!\nYou Will Be Redirected To Account.\n\n");
                            goto account;
                        } else {
                            system("cls");
                            fclose(help);
                            printf("You Don't Have Enough Points:( Try To Shop More\nYou Will Be Redirected To Account.\n\n");
                            goto account;
                        }
                    }
                    if (f == 2) {
                        if (cJSON_GetNumberValue(point_as_js) >= 200) {
                            char code_takhfif[11];
                            char *dummy;
                            code_takhfif[0] = '2';
                            code_takhfif[1] = '2';
                            dummy = randstring(8);
                            strcat(code_takhfif, dummy);
                            cJSON_ReplaceItemInObject(info_as_js, "discount_code", cJSON_CreateString(code_takhfif));
                            cJSON_ReplaceItemInObject(info_as_js, "points",
                                                      cJSON_CreateNumber(cJSON_GetNumberValue(point_as_js) - 200));
                            print_inf = cJSON_Print(info_as_js);
                            fclose(help);
                            help = fopen(username, "w");
                            fputs(print_inf, help);
                            fclose(help);
                            system("cls");
                            printf("Congrats:) Now You Have A 25percent Discount Code!\nYou Will Be Redirected To Account.\n\n");
                            goto account;
                        } else {
                            system("cls");
                            fclose(help);
                            printf("You Don't Have Enough Points:( Try To Shop More\nYou Will Be Redirected To Account.\n\n");
                            goto account;
                        }
                    }
                    if (f == 3) {
                        if (cJSON_GetNumberValue(point_as_js) >= 300) {
                            char code_takhfif[11];
                            char *dummy;
                            code_takhfif[0] = '3';
                            code_takhfif[1] = '3';
                            dummy = randstring(8);
                            strcat(code_takhfif, dummy);
                            cJSON_ReplaceItemInObject(info_as_js, "discount_code", cJSON_CreateString(code_takhfif));
                            cJSON_ReplaceItemInObject(info_as_js, "points",
                                                      cJSON_CreateNumber(cJSON_GetNumberValue(point_as_js) - 300));
                            print_inf = cJSON_Print(info_as_js);
                            fclose(help);
                            help = fopen(username, "w");
                            fputs(print_inf, help);
                            fclose(help);
                            system("cls");
                            printf("Congrats:) Now You Have A 50percent Discount Code!\nYou Will Be Redirected To Account.\n\n");
                            goto account;
                        } else {
                            system("cls");
                            fclose(help);
                            printf("You Don't Have Enough Points:( Try To Shop More\nYou Will Be Redirected To Account.\n\n");
                            goto account;
                        }
                    }
                    if (f == 0) {
                        fclose(help);
                        system("cls");
                        goto account;
                    }
                    system("cls");
                    fclose(help);
                    goto account;
                }
                if (numb == 5) {
                    printf("Please Enter The Products Name. You Can See Your Products From Orders History:)\nEnter 0 For Going Back\n\n");
                    char name_produ[100], cpy_name[100], your_comm[300], reading[400];
                    gets(name_produ);
                    if (name_produ[0] == '0') {
                        system("cls");
                        goto account;
                    }
                    strcpy(cpy_name, name_produ);
                    strcat(name_produ, "_");
                    strcat(name_produ, user_copy);
                    strcat(name_produ, "_com.json");
                    help = fopen(name_produ, "r");
                    if (help == 0) {
                        fclose(help);
                        system("cls");
                        printf("You Haven't Bought This Product Or This Isn't A Defined Product.\nYou'll Be Redirected To Account.\n\n");
                        goto account;
                    }
                    printf("Add Your Comment About This Product.\n");
                    fclose(help);
                    gets(your_comm);
                    strcat(cpy_name, "_comments.json");
                    pro = fopen(cpy_name, "r");
                    if (pro == 0) {
                        char *loco;
                        fclose(pro);
                        pro = fopen(cpy_name, "w");
                        cJSON *comment;
                        comment = cJSON_CreateObject();
                        cJSON_AddStringToObject(comment, "comments", your_comm);
                        loco = cJSON_Print(comment);
                        fputs(loco, pro);
                        fclose(pro);
                        printf("Thank You For Adding A Comment.\nEnter 0 To Go Back To Account.\n");
                        int dl;
                        scanf("%d%*c", &dl);
                        system("cls");
                        goto account;
                    }
                    fclose(pro);
                    char *jalop;
                    pro = fopen(cpy_name, "r+");
                    fread(reading, 1, 1000, pro);
                    cJSON *idea_as_js = cJSON_Parse(reading);
                    cJSON_ReplaceItemInObject(idea_as_js, "comments", cJSON_CreateString(your_comm));
                    jalop = cJSON_Print(idea_as_js);
                    fclose(pro);
                    pro = fopen(cpy_name, "w");
                    fputs(jalop, pro);
                    fclose(pro);
                    printf("Thank You For Adding A Comment.\nEnter 0 To Go Back To Account.\n");
                    int gf;
                    scanf("%d%*c", &gf);
                    system("cls");
                    goto account;
                }
                if (numb == 0) goto start;
            }
            if (strcmp(cJSON_GetStringValue(role_as_json), "2") == 0) {
                account2:
                printf("\nHi %s %s\n\n", cJSON_GetStringValue(firstname_as_json),
                       cJSON_GetStringValue(lastname_as_json));
                printf("What Do You Want To Do Today?\n");
                printf("Enter Your Willing Options Number\n1.Your Account\n2.Categories\n3.Add A Product\n4.Sold List\n5.Sale\n\n");
                printf("For Logging Out Enter 0\n");
                int numb;
                scanf("%d%*c", &numb);
                system("cls");
                if (numb == 1) {
                    char retailer_id[200];
                    int b;
                    help = fopen(username, "r");
                    fread(retailer_id, 1, 1000, help);
                    cJSON *id_as_json = cJSON_Parse(retailer_id);
                    cJSON *cash_as_json = cJSON_GetObjectItem(id_as_json, "money");
                    printf("Username: %s\n", user_copy);
                    printf("Firstname: %s\n", cJSON_GetStringValue(firstname_as_json));
                    printf("Lastname: %s\n", cJSON_GetStringValue(lastname_as_json));
                    printf("Cash In Hand: %g\n", cJSON_GetNumberValue(cash_as_json));
                    printf("Number of Successful Purchases:0\n");
                    printf("\nFor Going Back Please Enter 0\n");
                    scanf("%d%*c", &b);
                    goto account2;
                }
                if (numb == 2) {
                    char c;
                    category_LIST = fopen("List_of_Cats.json", "r");
                    c = fgetc(category_LIST);
                    printf("Available Categories Are:\n");
                    while (c != EOF) {
                        printf("%c", c);
                        c = fgetc(category_LIST);
                    }
                    fclose(category_LIST);
                    printf("\nFor Going Back Please Enter 0\n");
                    int m;
                    scanf("%d%*c", &m);
                    system("cls");
                    goto account2;
                }
                if (numb == 3) {
                    pro:
                    printf("Please Enter The Category Of The New Product.\nFor Going Back Enter 0.\n\n");
                    char category[50], copy_cat[300], cpy_name_cat[50];
                    gets(category);
                    strcpy(cpy_name_cat, category);
                    if (category[0] == '0') {
                        system("cls");
                        goto account2;
                    }
                    strcat(category, "_option.json");
                    category_LIST = fopen(category, "r");
                    if (category_LIST == 0) {
                        fclose(category_LIST);
                        printf("This Category Isn't Defined!\n Try Another One.\n\n");
                        goto pro;
                    }
                    fread(copy_cat, 1, 1000, category_LIST);
                    cJSON *name_cat = cJSON_Parse(copy_cat);
                    cJSON *str_as_json = cJSON_GetObjectItem(name_cat, "name");
                    if (strcmp(cJSON_GetStringValue(str_as_json), "leo") == 0) {
                        fclose(category_LIST);
                        char name_pro[60], copy_pro[60];
                        int Price, quantity;
                        char *string_product;
                        cJSON *Product;
                        printf("Please Enter The Products Name.\n");
                        gets(name_pro);
                        strcpy(copy_pro, name_pro);
                        strcat(name_pro, "_Product.json");
                        pro = fopen(name_pro, "w");
                        printf("Please Enter The Price(In Dollars).\n");
                        scanf("%d%*c", &Price);
                        printf("Please Enter The Existing Number Of This Product In The Inventory.\n");
                        scanf("%d%*c", &quantity);
                        Product = cJSON_CreateObject();
                        cJSON_AddStringToObject(Product, "product_name", copy_pro);
                        cJSON_AddStringToObject(Product, "category", cpy_name_cat);
                        cJSON_AddStringToObject(Product, "retailer_name", user_copy);
                        cJSON_AddNumberToObject(Product, "price", Price);
                        cJSON_AddNumberToObject(Product, "inventory", quantity);
                        cJSON_AddNumberToObject(Product, "percent_sale", 0);
                        string_product = cJSON_Print(Product);
                        fputs(string_product, pro);
                        fclose(pro);
                        pro = fopen("Product_LIST_manufactured.json", "a");
                        if (pro == 0) {
                            fclose(pro);
                            pro = fopen("Product_LIST_manufactured.json", "w");
                        }
                        fputs(copy_pro, pro);
                        fputs("\t  Category:", pro);
                        fputs(cpy_name_cat, pro);
                        fputs("\nRetailer:", pro);
                        fputs(user_copy, pro);
                        fputs("\t  Price:", pro);
                        fprintf(pro, "%d\t\t  Today's Existing Number:%d\n", Price, quantity);
                        fclose(pro);
                        // ye list rizi build mikonam az producta
                        help = fopen("Goods_Are-Good.json", "a");
                        if (help == 0) {
                            fclose(help);
                            help = fopen("Goods_Are-Good.json", "w");
                        }
                        fputs(copy_pro, help);
                        fputs("\n", help);
                        fclose(help);
                        system("cls");
                        printf("The Product Has Been Successfully Added:)\n\n");
                        goto account2;
                    }
                    goto account2;
                }
                if (numb == 4) {
                    char c;
                    help = fopen("purchases_good.json", "r");
                    if (help == 0) {
                        fclose(help);
                        printf("There Isn't Any purchase history!\nWe Better Wait For Our Customers To Buy Stuff.\n\n");
                        goto account2;
                    }
                    c = fgetc(help);
                    printf("Your Shop's History Is:\n\n");
                    while (c != EOF) {
                        printf("%c", c);
                        c = fgetc(help);
                    }
                    fclose(help);
                    printf("For Going Back Please Enter 0.\n\n");
                    int r;
                    scanf("%d%*c", &r);
                    system("cls");
                    goto account2;
                }
                if (numb == 5) {
                    sale:
                    printf("Enter Your Willing Options Number\n1.Start A Sale\n2.Finish A Sale\n3.Take A Look At The Current Sales\nFor Going Back Enter 0\n\n");
                    int g;
                    scanf("%d%*c", &g);
                    if (g == 0) {
                        system("cls");
                        goto account2;
                    }
                    if (g == 1) {
                        char name_prod[60], copy_info[400];
                        int percent;
                        char *cpy_sale;
                        printf("Enter The Product's Name.\nFor Going Back Enter 0\n");
                        gets(name_prod);
                        if (name_prod[0] == '0') {
                            system("cls");
                            goto sale;
                        }
                        strcat(name_prod, "_Product.json");
                        help = fopen(name_prod, "r+");
                        if (help == 0) {
                            fclose(help);
                            system("cls");
                            printf("Undefined Product! Please Try Again.\n\n");
                            goto sale;
                        }
                        printf("Enter The Amount Of Discount You Want To Offer(between 1 to 100)\n");
                        scanf("%d%*c", &percent);
                        fread(copy_info, 1, 1000, help);
                        cJSON *info_product_json = cJSON_Parse(copy_info);
                        cJSON_ReplaceItemInObject(info_product_json, "percent_sale", cJSON_CreateNumber(percent));
                        cpy_sale = cJSON_Print(info_product_json);
                        fclose(help);
                        help = fopen(name_prod, "w");
                        fputs(cpy_sale, help);
                        fclose(help);
                        system("cls");
                        printf("The Changes Are Applied:)\n\n");
                        goto sale;
                    }
                    if (g == 2) {
                        char name_prod[60], copy_info[400];
                        char *cpy_sale;
                        printf("Enter The Product's Name.\nFor Going Back Enter 0\n");
                        gets(name_prod);
                        if (name_prod[0] == '0') {
                            system("cls");
                            goto sale;
                        }
                        strcat(name_prod, "_Product.json");
                        help = fopen(name_prod, "r+");
                        if (help == 0) {
                            fclose(help);
                            system("cls");
                            printf("Undefined Product! Please Try Again.\n\n");
                            goto sale;
                        }
                        fread(copy_info, 1, 1000, help);
                        cJSON *info_product_js = cJSON_Parse(copy_info);
                        cJSON_ReplaceItemInObject(info_product_js, "percent_sale", cJSON_CreateNumber(0));
                        cpy_sale = cJSON_Print(info_product_js);
                        fclose(help);
                        help = fopen(name_prod, "w");
                        fputs(cpy_sale, help);
                        fclose(help);
                        system("cls");
                        printf("The Changes Are Applied:(\n\n");
                        goto sale;
                    }
                    if (g == 3) {
                        watch_discount:
                        pro = fopen("Goods_Are-Good.json", "r");
                        if (pro == 0) {
                            fclose(pro);
                            printf("There Are No Defined Products.\n\n");
                            goto sale;
                        }
                        char c;
                        c = fgetc(pro);
                        printf("Defined Products Are:\n");
                        while (c != EOF) {
                            printf("%c", c);
                            c = fgetc(pro);
                        }
                        fclose(pro);
                        printf("\n\nEnter The Product's Name.\nFor Going Back Enter 0\n");
                        char sale_prod[60], copy_sale[400], sale_name_cpy[70];
                        gets(sale_prod);
                        if (sale_prod[0] == '0') {
                            system("cls");
                            goto sale;
                        }
                        strcpy(sale_name_cpy, sale_prod);
                        strcat(sale_prod, "_Product.json");
                        help = fopen(sale_prod, "r+");
                        if (help == 0) {
                            fclose(help);
                            system("cls");
                            printf("Undefined Product! Please Try Again.\n\n");
                            goto sale;
                        }
                        fread(copy_sale, 1, 1000, help);
                        cJSON *sale_product_json = cJSON_Parse(copy_sale);
                        cJSON *percent_sale = cJSON_GetObjectItem(sale_product_json, "percent_sale");
                        printf("The %s Is ON %g percent Sale!\n\n", sale_name_cpy, cJSON_GetNumberValue(percent_sale));
                        fclose(help);
                        printf("Enter 6 To Check Another Product.\nEnter Any Other One Digit Number To Go Back To Pervious Menu.\n\n");
                        int j;
                        scanf("%d%*c", &j);
                        if (j == 6) {
                            system("cls");
                            goto watch_discount;
                        } else {
                            system("cls");
                            goto sale;
                        }
                    }
                }
                if (numb == 0) goto start;
            }
            if (strcmp(cJSON_GetStringValue(role_as_json), "3") == 0) {
                account1:
                printf("\nHi %s %s\n\n", cJSON_GetStringValue(firstname_as_json),
                       cJSON_GetStringValue(lastname_as_json));
                printf("What Do You Want To Do Today?\n");
                printf("Enter Your Willing Options Number\n1.Your Account\n2.User list\n3.Banning\n4.UnBanning\n5.Add A Category\n6.Comments\n\n");
                printf("\nEnter 0 To Log Out\n");
                int numb;
                scanf("%d%*c", &numb);
                system("cls");
                if (numb == 0) goto start;
                if (numb == 1) {
                    int c;
                    printf("Username: %s\n", user_copy);
                    printf("Firstname: %s\n", cJSON_GetStringValue(firstname_as_json));
                    printf("Lastname: %s\n", cJSON_GetStringValue(lastname_as_json));
                    printf("Number of Successful Purchases:0\n");
                    printf("\nFor Going Back Please Enter 0\n");
                    scanf("%d%*c", &c);
                    goto account1;
                }
                if (numb == 2) {
                    char c;
                    User_List = fopen("List_of_USERS.json", "r");
                    c = fgetc(User_List);
                    printf("Signed Users Are:\n");
                    while (c != EOF) {
                        printf("%c", c);
                        c = fgetc(User_List);
                    }
                    fclose(User_List);
                    printf("\nFor Going Back Please Enter 0\n");
                    int z;
                    scanf("%d%*c", &z);
                    system("cls");
                    goto account1;
                }
                if (numb == 3) {
                    ban:
                    printf("Please Enter The Username of The Poor User You Want To Ban\n");
                    printf("If You Want To Go Back Enter 0\n");
                    char name[40], copy_json[300];
                    char *copy_cjson_info;
                    gets(name);
                    if (name[0] == '0') {
                        system("cls");
                        goto account1;
                    }
                    strcat(name, ".json");
                    Ban = fopen(name, "r+");
                    if (Ban == 0) {
                        fclose(Ban);
                        printf("There Isn't A User With This Username.\nTry Again\n\n");
                        goto ban;
                    }
                    fread(copy_json, 1, 1000, Ban);
                    cJSON *info_js = cJSON_Parse(copy_json);
                    cJSON *role_js = cJSON_GetObjectItem(info_js, "role");
                    if (strcmp(cJSON_GetStringValue(role_js), "3") == 0) {
                        fclose(Ban);
                        printf("This User is An Admin.\n Try Again\n\n");
                        goto ban;
                    } else {
                        cJSON_ReplaceItemInObject(info_js, "Situation", cJSON_CreateString("Banned"));
                        copy_cjson_info = cJSON_Print(info_js);
                        fclose(Ban);
                        Ban = fopen(name, "w");
                        fputs(copy_cjson_info, Ban);
                        fclose(Ban);
                        printf("This User is Now Banned And Can't Login:(\n\n");
                    }
                    printf("\nFor Going Back Please Enter 0\n");
                    int x;
                    scanf("%d%*c", &x);
                    system("cls");
                    goto account1;
                }
                if (numb == 4) {
                    unban:
                    printf("Please Enter The Username of The Lucky User You Want To Unban\n");
                    printf("If You Want To Go Back Enter 0\n");
                    char name[40], copy_js[350];
                    gets(name);
                    if (name[0] == '0') {
                        system("cls");
                        goto account1;
                    }
                    strcat(name, ".json");
                    Unban = fopen(name, "r+");
                    if (Unban == 0) {
                        fclose(Unban);
                        printf("There Isn't A User With This Username.\nTry Again\n\n");
                        goto unban;
                    } else {
                        char *cpy;
                        fread(copy_js, 1, 1000, Unban);
                        cJSON *inf_js = cJSON_Parse(copy_js);
                        cJSON *situation_js = cJSON_GetObjectItem(inf_js, "Situation");
                        if (strcmp(cJSON_GetStringValue(situation_js), "Banned") == 0) {
                            cJSON_ReplaceItemInObject(inf_js, "Situation", cJSON_CreateString(""));
                            cpy = cJSON_Print(inf_js);
                            fclose(Unban);
                            Unban = fopen(name, "w");
                            fputs(cpy, Unban);
                            fclose(Unban);
                            printf("The User Is Now Free To Login:)\n\n");
                        } else {
                            fclose(Unban);
                            printf("This User Isn't Banned!!\nTry Another One\n\n");
                            goto unban;
                        }
                    }
                    printf("\nFor Going Back Please Enter 0\n");
                    int y;
                    scanf("%d%*c", &y);
                    system("cls");
                    goto account1;
                }
                if (numb == 5) {
                    char category[100], copy_cat[100];
                    char *copy_name;
                    category_LIST = fopen("List_of_Cats.json", "a");
                    if (category_LIST == 0) {
                        fclose(category_LIST);
                        category_LIST = fopen("List_of_Cats.json", "w");
                    }
                    printf("\nEnter A Name You Want to Use For The Category\n");
                    gets(category);
                    strcpy(copy_cat, category);
                    copy_name = category;
                    strcat(copy_name, "\n");
                    fputs(copy_name, category_LIST);
                    fclose(category_LIST);
                    strcat(copy_cat, "_option.json");
                    category_LIST = fopen(copy_cat, "w");
                    cJSON *cat_name;
                    char *buff;
                    cat_name = cJSON_CreateObject();
                    cJSON_AddStringToObject(cat_name, "name", "leo");
                    buff = cJSON_Print(cat_name);
                    fputs(buff, category_LIST);
                    fclose(category_LIST);
                    system("cls");
                    printf("You Will Be Redirected To Previous Menu. Please Enter 0\n\n");
                    int v;
                    scanf("%d%*c", &v);
                    goto account1;
                }
                if (numb == 6) {
                    char name_good[100], copy_good[100], read_comment[400];
                    pro = fopen("Goods_Are-Good.json", "r");
                    if (pro == 0) {
                        fclose(pro);
                        printf("There Are No Defined Products.\n\n");
                        goto sale;
                    }
                    char c;
                    c = fgetc(pro);
                    printf("Defined Products Are:\n");
                    while (c != EOF) {
                        printf("%c", c);
                        c = fgetc(pro);
                    }
                    fclose(pro);
                    printf("\nEnter The Product's Name You Want To Read Comments About.\nEnter 0 To Go Back\n");
                    gets(name_good);
                    if (name_good[0] == '0') {
                        system("cls");
                        goto account1;
                    }
                    strcpy(copy_good, name_good);
                    strcat(name_good, "_comments.json");
                    help = fopen(name_good, "r+");
                    if (help == 0) {
                        fclose(help);
                        system("cls");
                        printf("There Isn't Any Comments About This Product Or This Isn't Even A Product.\nYou'll Be Redirected To Account.\n\n");
                        goto account1;
                    }
                    fread(read_comment, 1, 1000, help);
                    cJSON *comm_inf_js = cJSON_Parse(read_comment);
                    cJSON *comment_as_js = cJSON_GetObjectItem(comm_inf_js, "comments");
                    printf("Existing Comments To This Product Are:\n\n%s", cJSON_GetStringValue(comment_as_js));
                    printf("\n\nIf You Want To approve This Comment Enter 1\nIf Not Enter Any Other One Digit Number\n");
                    int coma;
                    scanf("%d%*c", &coma);
                    system("cls");
                    if (coma == 1) {
                        fclose(help);
                        strcat(copy_good, "_comList.json");
                        help = fopen(copy_good, "a");
                        if (help == 0) {
                            fclose(help);
                            help = fopen(copy_good, "w");
                        }
                        fputs(cJSON_GetStringValue(comment_as_js), help);
                        fputs("\n\n", help);
                        fclose(help);
                        system("cls");
                        printf("Done!\nYou'll Be Redirected To Account.\n\n");
                        goto account1;
                    }
                    fclose(help);
                    system("cls");
                    printf("OK, You Disagreed!\nYou'll Be Redirected To Account.\n\n");
                    goto account1;
                }
            }
            return 0;
        }
    }
    if (num[0] == '3') {
        printf("Good Luck");
        return 0;
    }
    return 0;
}
