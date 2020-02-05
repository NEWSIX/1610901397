a="i am lol"
print(a)

#import os,sys
#Score,Mid,Final=-1,-1,-1
def main():
    #while(Score) in range(0,50):                   
        Score = float(input("Accumulated score : "))
    #while not (Mid) in range(0,20):               
        Mid = float(input("Midterm Exam : "))
    #while not (Final) in range(0,30):
        Final = float(input("Fianl Exam : "))
        print('')
        
        Sum = Score+Mid+Final
        if(Sum>=80 and Sum<=100):
            print("summation of score is :",Sum,"\nYour Grade is : A")
        elif(Sum>=75 and Sum<=79):
            print("summation of score is :",Sum,"\nYour Grade is : B+")
        elif(Sum>=70 and Sum<=74):
            print("summation of score is :",Sum,"\nYour Grade is : B")
        elif(Sum>=65 and Sum<=69):
            print("summation of score is :",Sum,"\nYour Grade is : C+")
        elif(Sum>=60 and Sum<=64):
            print("summation of score is :",Sum,"\nYour Grade is : C")
        elif(Sum>=55 and Sum<=59):
            print("summation of score is :",Sum,"\nYour Grade is : D+")
        elif(Sum>=50 and Sum<=54):
            print("summation of score is :",Sum,"\nYour Grade is : D")
        elif(Sum>=0 and Sum<=49):
            print("summation of score is :",Sum,"\nYour Grade is : F")
        else:
            print("score ERROR!")
            main()
            
while(True):
    main()
    a = input("\nPress any key to do Agian or Press xx to exit : ... ")
    if(a.lower()== 'xx'):
        exit()
    else:
        ()