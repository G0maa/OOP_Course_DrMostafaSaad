#include <bits/stdc++.h>
#include "json.hpp"
using namespace std;
using namespace json;

// Used my 13_03.cpp code and build the 'Factory'.

class SquarePaymentAPI {
public:
    bool static WithDrawMoney(string JSONQuery) {
        return true;
    }
};

class PayPalCreditCard {
public:
	string name;
	string address;
	string id;
	string expire_date;
	int ccv;
};

class PayPalOnlinePaymentAPI {
public:
	void SetCardInfo(const PayPalCreditCard* const card) {
	}
	bool MakePayment(double money) {
		return true;
	}
};

class StripeUserInfo {
public:
	string name;
	string address;
};

class StripeCardInfo {
public:
	string id;
	string expire_date;
};

class StripePaymentAPI {
public:
	bool static WithDrawMoney(StripeUserInfo user,
							  StripeCardInfo card,
							  double money) {
		return true;
	}
};

class TransactionInfo {
public:
	double required_money_amount;
	string name;
	string address;
	string id;
	string expire_date;
	int ccv;
};

class IPayment { // after I was stuck for about 20mins I saw solution, this line is the only line I saw, so I'd say it's a hint :)
protected:
    TransactionInfo transaction_info;
public:
    IPayment(const TransactionInfo &transaction_info) : transaction_info(transaction_info) {

    }

    virtual void Set() = 0;
    virtual bool Pay() = 0;
    
    ~IPayment() {

    }
};


class IStripe : public IPayment {
private:
    StripeUserInfo user_info;
    StripeCardInfo card_info;
    StripePaymentAPI api;
public:
    using IPayment::IPayment;

    virtual void Set() override {
        // Obviously some validations and/or type change might happen here :)
        user_info.name = transaction_info.name;
        user_info.address = transaction_info.address;

        card_info.id = transaction_info.id;
        card_info.expire_date = transaction_info.expire_date;
    }

    virtual bool Pay() override {
        return api.WithDrawMoney(user_info, card_info, transaction_info.required_money_amount);
    }
};

class ISquare : public IPayment {
private:
    JSON json_obj;
public:
    using IPayment::IPayment;

    virtual void Set() override {
        json_obj["card_info"] = Object();
        json_obj["card_info"]["CCV"] = transaction_info.ccv;
        json_obj["card_info"]["DATE"] = transaction_info.expire_date;
        json_obj["card_info"]["ID"] = transaction_info.id;
        json_obj["money"] = transaction_info.required_money_amount;
        json_obj["user_info"] = Array(transaction_info.name, transaction_info.address);

        cout << json_obj;
    }

    virtual bool Pay() override {
        ostringstream oss;
        oss << json_obj;
        string query = oss.str();

        return SquarePaymentAPI::WithDrawMoney(query);
    }
};



class IPayPal : public IPayment {
private:
    PayPalOnlinePaymentAPI *api { };
    PayPalCreditCard card;
public:
    using IPayment::IPayment;

    virtual void Set() override {
        // Obviously some validations and/or type change might happen here :)
        card.name = transaction_info.name;
        card.address = transaction_info.address;
        card.id = transaction_info.id;
        card.expire_date = transaction_info.expire_date;
        card.ccv = transaction_info.ccv;
    }

    virtual bool Pay() override {
        api->SetCardInfo(&card);
        return api->MakePayment(transaction_info.required_money_amount);
    }
};

// Sneakly copied from 13_03 doc solution.
// Factory shouldn't be exposed to raidiation (data),
// Factory bad... didn't want to change code...
class Factory {
public:
    static IPayment* GetPaymentMethod(const TransactionInfo &transaction_info) {
        if(true)
            return new ISquare(transaction_info);
        else if (false)
            return new IPayPal(transaction_info);
        else
            return new IStripe(transaction_info);
        
        return nullptr;
    }
};

// Note after seeing solution => I didn't 'build' a factory, see doc solution for more info.
class Craigslist {
	public:
	bool Pay(const TransactionInfo &trnasaction_info) {

		// Some logic choosing PayPal or Stripe or other... result:
        IPayment *payment = Factory::GetPaymentMethod(trnasaction_info);
        return payment->Pay();
	}
};


int main() {
    TransactionInfo info;
    info.address = "Egypt";
    info.ccv = 123;
    info.expire_date = "2022";
    info.id = "231";
    info.name = "Noriel";
    info.required_money_amount = 750;
    ISquare obj(info);
    obj.Set();
    
    cout << "\n\n Bye :) \n\n";
	return 0;
}
