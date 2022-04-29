#include <bits/stdc++.h>
using namespace std;

// PayPalCreditCard and PayPalOnlinePaymentAPI are NOT our code. They are Paypal API.
// We have to use them to be able to call PayPal service


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

// Note after seeing solution => I didn't 'build' a factory, see doc solution for more info.
class Craigslist {
	public:
	bool Pay(const TransactionInfo &trnasaction_info) {

		// Some logic choosing PayPal or Stripe or other... result:
        IPayment *payment = new IPayPal(trnasaction_info);
        payment->Pay();
	}
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


int main() {

    
	return 0;
}
