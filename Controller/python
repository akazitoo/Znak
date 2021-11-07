
def login(Username=None, Password=None):
    Username = input("Digite seu username:")
    Password = input("Digite sua senha:")
    
    if not len(Username or Password) < 1:
        if True:
          db = open("users.txt", "r")
          d = []
          f = []
          for i in db:
              a = i.split(", ")
              d.append(a[0])
              b = a[1].strip("\n")
              f.append(b)
              data = dict(zip(d, f))
          try:
            if data[Username]:
                if Password == data[Username]:
                  print("Tudo certo!")
                  print("Olá, ", Username)
                else:
                  print("Senha Incorreta")
                  login()
          except:
            print("Usuário não existe")






def register(Username=None, Password1=None, Password2=None):
    Username = input("Escolha um username:")
    Password1 = input("Crie uma senha:")
    Password2 = input("Confirme a senha:")
    db = open("users.txt", "r")
    d = []
    for i in db:
        a = i.split(", ")
        d.append(a[0])
    if not len(Password1)<4:
        db = open("users.txt", "r")
        if not Username == None:
            if Username in d:
                print("Este username já existe")
                register()		
            else:
                if Password1 == Password2:
                    db = open("users.txt", "a")
                    db.write(Username+" , "+str(Password1)+"\n")
                    print("Conta criada!")
                else:
                    print("Senhas não coincidem!")
                    register()
    else:
        print("Senha muito curta")



def home(option=None):
	print("Olá, você já tem uma conta?")
	option = input("S | N: ")
	if option == "S":
		login()
	elif option == "N":
		register()
	else:
		print("Por favor digite um caso válido")

home()
