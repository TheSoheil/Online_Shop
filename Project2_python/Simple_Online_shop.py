import os


def retailer(name_user):
    file = open(name_user + ".txt", "r")
    content = file.readlines()
    user_saver = content[0]
    save_user = user_saver[:-1]
    print("Welcome " + content[2])
    print("\n1.Account Info\n2.Categories\n3.Add_Product\n4.Sale_list\n")
    print("Any other input will redirect you to main menu.\n")
    x = int(input("Please Enter your Willing Number To Continue: "))
    if x == 1:
        print(" \nUsername: " + content[0])
        print("firstname: " + content[2])
        print("Lastname: " + content[3])
        print("Money: " + content[5])
        print("Number of Purchases: " + content[6])
        input("\nEnter Any Number for Proceeding to Previous Menu: ")
        file.close()
        return retailer(save_user)
    if x == 2:
        file.close()
        if not os.path.exists("categories_cat10.txt"):
            file = open("categories_cat10.txt", "w")
            file.write("Burgers\nPizza\nSalad\nFries\nDrinks\n")
            file.close()
        print("Available Categories Are:\nBurgers\nPizza\nSalad\nFries\nDrinks\n")
        input("Enter Any Number to Proceed to Previous Menu: ")
        return retailer(save_user)
    if x == 3:
        file.close()
        prod_name = input("Enter Products Name: ")
        prod_price = int(input("Enter Products Price: "))
        prod_category = input("Enter Products Category: ")
        file = open("categories_cat10.txt", "r")
        info_cat = file.readlines()
        count = 0
        for i in range(0, 5):
            if info_cat[i] == prod_category + "\n":
                count += 1
        if count == 0:
            print("\ninvalid Category. You will be redirected to previous menu\n ")
            file.close()
            return retailer(save_user)
        prod_quantity = int(input("How Many of This Product is Available? "))
        file = open(prod_name + "_prod.txt", "w")
        file.write(
            prod_name + "\n" + str(prod_price) + "\n" + prod_category + "\n" + str(prod_quantity) + "\n" + save_user)
        file.close()
        if not os.path.exists("products_prod10.txt"):
            file = open("products_prod10.txt", "w")
            file.close()
        file = open("products_prod10.txt", "a")
        file.write(
            "\t\t\tname: " + prod_name + "\nprice: " + str(prod_price) + "  availability: " + str(
                prod_quantity) + "\n Category: " + prod_category + "  By:" + save_user + "\n")
        file.close()
        print("Done:)\n\n")
        return retailer(save_user)

    if x == 4:
        file.close()
        if not os.path.exists(save_user + "_sale_hist10.txt"):
            print("\nNothing Has been Sold Yet:( Try Again Later.")
            return retailer(save_user)
        file = open(save_user + "_sale_hist10.txt", "r")
        print(file.read())
        file.close()
        input("Enter Any number to proceed to customer menu")
        return retailer(save_user)
    if x != 1 and x != 2 and x != 3 and x != 4:
        return main()


def customer(check_name):
    file = open(check_name + ".txt", "r")
    content = file.readlines()
    customer_saver = content[0]
    save_name = customer_saver[:-1]
    print("Welcome " + content[2])
    print("\n1.Account Info\n2.Products\n3.History\n")
    print("Any other input will redirect you to main menu.\n")
    f = int(input("Please Enter Your Willing Number To Continue: "))
    if f == 1:
        print("\nUsername: " + content[0])
        print("Firstname: " + content[2])
        print("Lastname: " + content[3])
        print("Money: " + content[5])
        print("Number of Purchases: " + content[6])
        input("\nEnter Any Number for Proceeding to Previous Menu: ")
        file.close()
        return customer(save_name)
    if f == 2:
        if not os.path.exists("products_prod10.txt"):
            print("\nThere isn't Any Products Yet! Retailers Will Add some soon:) Try Later.\n")
            return customer(save_name)
        file = open("products_prod10.txt", "r")
        print(file.read())
        file.close()
        print("\n1.Buy\n2.Back")
        v = int(input("Enter Your Willing Number: "))
        if v == 2:
            return customer(save_name)
        if v == 1:
            food = input("\nEnter The Exact Product Name You WANT to Buy: ")
            if not os.path.exists(food + "_prod.txt"):
                print("Wrong Product name! you'll be Redirected to previous Menu.\n")
                return customer(save_name)
            how_many = int(input("How Many of This Product You Want to Buy? "))
            file = open(food + "_prod.txt", "r")
            saving = file.readlines()
            if int(saving[3]) < how_many:
                file.close()
                print("\nWe Don't Have this Much Right Now:(\n you will face previous menu now.\n")
                return customer(save_name)
            save_price = int(saving[1])
            save_product = saving[0]
            save_user = saving[4]
            file.close()
            # saving history of purchase for customer
            if not os.path.exists(save_name + "_hist20.txt"):
                file = open(save_name + "_hist20.txt", "w")
                file.close()
            file = open(save_name + "_hist20.txt", "a")
            file.write(save_product + "cost: " + str(save_price * how_many) + "  amount: " + str(how_many) + "\n")
            file.close()
            # subtracting money from buyers account and adding number of purchases
            file = open(save_name + ".txt", "r")
            edit = file.readlines()
            edit[5] = str(int(edit[5]) - (how_many * save_price)) + "\n"
            edit[6] = str(int(edit[6]) + 1)
            file.close()
            file = open(save_name + ".txt", "w")
            file.writelines(edit)
            file.close()
            # saving purchase history for retailer
            if not os.path.exists(save_user + "_sale_hist10.txt"):
                file = open(save_user + "_sale_hist10.txt", "w")
                file.close()
            file = open(save_user + "_sale_hist10.txt", "a")
            file.write("user: " + save_name + "\tproduct: " + save_product + "\nprice: " + str(
                save_price * how_many) + "\tAmount:" + str(how_many) + "\n")
            file.close()
            # adding money to retailers account
            file = open(save_user + ".txt", "r")
            copy_paste = file.readlines()
            copy_paste[5] = str(int(copy_paste[5]) + (how_many * save_price)) + "\n"
            file.close()
            file = open(save_user + ".txt", "w")
            file.writelines(copy_paste)
            file.close()
            print("\nDone! Enjoy Your Meal:)")
            return customer(save_name)
        if v != 1 and v != 2:
            print("Wrong input! You will face previous menu.\n")
            return customer(save_name)
    if f == 3:
        if not os.path.exists(save_name + "_hist20.txt"):
            print("\nYou Haven't Bought Anything Yet! Try Buying First.\n")
            return customer(save_name)
        file = open(save_name + "_hist20.txt", "r")
        print(file.read())
        file.close()
        input("\nEnter Any Number to Proceed to Previous Menu.")
        return customer(save_name)
    if f != 1 and f != 2 and f != 3:
        return main()


def role(num_role):
    if num_role == 1:
        return "Customer"
    if num_role == 2:
        return "Retailer"
    if num_role != 1 and num_role != 2:
        print("\nWrong Input! Try Again\n")
        b = int(input("\n1.Customer\n2.Retailer\nPlease Enter Your Desired Role: "))
        return role(b)


def login():
    check_name = input("\nEnter Your Username: ")
    if not os.path.exists(check_name + ".txt"):
        print("\n There isn't Such Username in directory\nYou will be Redirected to Main Menu.\n\n")
        main()
    check_pass = input("\nEnter Your Password: ")
    file = open(check_name + ".txt", "r")
    content = file.readlines()
    if content[1] != (check_pass + "\n"):
        print("\nWrong Password!!\nYou will be Redirected to Main Menu.\n\n")
        main()
    if content[4] == "Retailer" + "\n":
        file.close()
        retailer(check_name)
    if content[4] == "Customer" + "\n":
        file.close()
        customer(check_name)


def signup():
    username = input("Welcome\nPlease Enter Your Desired Username: ")
    if os.path.exists(username + ".txt"):
        print("\nThis Username Already Exists.\n Try Again.\n")
        signup()
    password = input("\nPlease Enter Your Desired Password: ")
    first_name = input("\nPlease Enter Your Desired Firstname: ")
    last_name = input("\nPlease Enter Your Desired Lastname: ")
    naghsh = int(input("\n1.Customer\n2.Retailer\nPlease Enter Your Desired Role: "))
    save_role = role(naghsh)
    start_money = int(input("\nPlease Enter Your Desired Money to Start: "))
    file = open(username + ".txt", "w")
    file.write(username + "\n" + password + "\n")
    file.write(first_name + "\n" + last_name + "\n")
    file.write(save_role + "\n" + str(start_money) + "\n")
    file.write("0")
    file.close()
    print("\n\nYour Account Have Been Successfully Created:)\n")
    print("\nYou Will Be Redirected to The Main Menu.\n\n")
    main()


def menu(num_menu):
    if num_menu == 1:
        signup()
    if num_menu == 2:
        login()
    if num_menu == 3:
        return 0
    if num_menu != 1 and num_menu != 2 and num_menu != 3:
        a = int(input("Wrong input. Try Again: "))
        menu(a)
    return 0


def main():
    print("1.Sign Up")
    print("2.Login")
    print("3.Exit")
    menu_number = int(input("Please Enter Your Willing Number To Continue: "))
    menu(menu_number)
    return 0


main()
