#include <iostream>
#include <string>

class Account {
	private:
		    const std::string _holder;
		        int _balance = 0;

	public:
			    void print() {
				            std::cout << "Account of: " << _holder << " has balance: " << _balance << std::endl;
					        }

			        bool deposit(int ammount) {

                                if(ammount >= 0){

                                    _balance += ammount;  
                                    
                                    return true;

                                }

                                return false;
                                
					        
						    }

				    bool withdraw(int ammount) {
                                
							if(ammount <= _balance && ammount >= 0){

                                    _balance -= ammount;

                                    return true;

                                } 

                                return false;

						    }

				        Account(std::string holder)
						        : _holder(holder) {
								    }

					    Account(std::string holder, int balance)
						            : _holder(holder)
							              , _balance(balance) {
									          }
};

class Loan {
	private:
		    Account& _parent;

		        int _ammount;

	public:

			    Loan(Account& parent, int ammount)
				            : _parent(parent)
					              , _ammount(ammount) {
							              _parent.deposit(ammount);
								          }

			        void payoff(int ammount) {
					        _parent.withdraw(ammount);
						    }

				    ~Loan() {
					            payoff(_ammount);
						        }
};

int main() {
	    Account account("Petr");
	        account.print();
		    {
			            Loan loan(account, 10000);
				            account.print();
			}  
				account.print();
				std::cout << "Deposit: " << account.deposit(500) << std::endl;
				account.print();
				std::cout << "Withdraw: " << account.withdraw(100) << std::endl;			
		        account.print();
			
}

