#include <iostream>
#include "main.h"
#include "list.h"
#include "iterator.h"

using namespace std;

int main() {
    
    List <string> d;
    List <string> tip;
    List <int> num;
    List <int> sec;
    List <int> tel;
    
    try{
        
        d.addLast("Sana");
        d.addLast("Haider");
        tip.addLast("Aysha");
        tip.addLast("Sarah");
        
        tip.addLast("Roxy");
        tip.addLast("Jam");
        
        num.addLast(5);
        num.addLast(10);
        num.addLast(15);
        
        sec.addLast(1);
        sec.addLast(2);
        sec.addLast(3);
        sec.addLast(4);
        sec.addLast(5);
        
        ListIterator<int> li = sec.listIterator();
        cout << li.next() << endl;
        cout << li.next() << endl;
        cout << li.previous() << endl;
        cout << li.next() << endl;

        
        /*ListIterator<int> li = sec.listIterator();
        cout << li.next() << endl;
        cout << li.next() << endl;
        cout << li.next() << endl;
        cout << li.next() << endl;

        cout << li.previous() << endl;
        cout << li.previous() << endl;
        cout << li.previous() << endl;
        
        cout << li.next() << endl;
        cout << li.next() << endl;*/
        

        /*ListIterator<int> li = sec.listIterator();
        cout << li.next() << endl;
        cout << li.next() << endl;
        cout << li.next() << endl;
        cout << li.next() << endl;*/
        
        /*ListIterator<int> li = sec.listIterator(4);
        
        cout << li.previous() << endl;
        cout << li.previous() << endl;
        cout << li.previous() << endl;
        cout << li.previous() << endl;*/

        
        /*cout << d;
        
        d.addAll(int(0), tip);
        
        cout << d;*/
        
        /*cout << num;
        
        num.addAll(1, sec);
        
        cout << num;*/
        
        /*int * x = sec.toArray();
        
        for( unsigned i = 0; i < sec.size(); i++ ){
            cout << x[i] << endl;
        }
        
        delete [] x;*/
        
        /*cout << num.removeLastOccurrence(15) << endl;
        
        cout << num.size() << endl;
        
        cout << num;
        
        cout << endl;
        
        num.printInternal();
        
        cout << endl;*/
        
    }
    catch ( NoSuchObject& e ){
        cout << e.what() << endl;
    }
    catch ( invalid_argument& e ){
        cout << "Invalid argument: " << e.what() << endl;
    } // catch
    catch ( logic_error& e ){
        cout << "Logic error: " << e.what() << endl;
    } // catch
    catch ( bad_alloc& e){
        cout << "Bad alloc: " << e.what() << endl;
    }
    catch (...){
        cout << "Unkown exception!" << endl;
    } // catch
    
    return 0;
    
}
