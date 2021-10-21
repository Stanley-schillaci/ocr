import numpy as np
np.random.seed(1)

op = "XOR" #choisir entre "XOR, "OR" et "AND"
'''
Fonction pour ramener un nombre sur R dans un intervalle [0,1]
'''
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

'''
Calcul de la dérive d'une fonction sigmoid
'''
def sigmoidPrime(x):
    return x * (1 - x)



'''
        PARTI DONNEES
'''

#input d'entré (neuronne d'input)
inputs = np.array([
                    [0, 0],
                    [0, 1],
                    [1, 0],
                    [1, 1]
])

#Répones attendu
#pour le xor
RXOR = np.array([
                     [0],
                     [1],
                     [1],
                     [0]
])
#pour le ou
ROR = np.array([
                     [0],
                     [1],
                     [1],
                     [1]
])

#pour le and
RAND = np.array([
                     [0],
                     [0],
                     [0],
                     [1]
])

'''input de test'''
#Test
inputs_test = np.array([[0, 0],
                        [0, 1],
                        [1, 0],
                        [1, 1],
])

#Répones attendu
#pour le xor
TXOR = np.array([
                     [0],
                     [1],
                     [1],
                     [0]
])
#pour le ou
TOR = np.array([
                     [0],
                     [1],
                     [1],
                     [1]
])

#pour le and
TAND = np.array([
                     [0],
                     [0],
                     [0],
                     [1]
])

'''
    Dimensions du reseau de neuronne
    #Nombre de neurones d'entree
    #Nombre de neurones dans le hidden layer
    #Nombre de neurones de sortie
'''

nb_input_neurons = 2
nb_hidden_neurons = 4
nb_output_neurons = 1

'''
    Initialisation des poids de manière alétoires
'''

hidden_layer_weights = 2 * np.random.random((nb_input_neurons, nb_hidden_neurons)) - 1  # random dans l'intervalle[-1,1]
output_layer_weights = 2 * np.random.random((nb_hidden_neurons, nb_output_neurons)) - 1 # random dans l'intervalle[-1,1]

print(hidden_layer_weights);

'''
    Phase d'entrainement
'''

nb_training_iteration = 5000

if(op == "XOR"):
    R = RXOR
    T = TXOR
elif(op == "OR"):
    R = ROR
    T = TOR
else:
    R = RAND
    T = TAND

for i in range(nb_training_iteration):

    #FEED FORWARD (parcour du reseau dans le sens input -> output

    input_layer = inputs
    hidden_layer = sigmoid(np.dot(input_layer, hidden_layer_weights))
    output_layer = sigmoid(np.dot(hidden_layer, output_layer_weights))


    #ACKPROPAGATION (parcour du reseau dans le sens input <- output

    output_layer_error = (R- output_layer)

    #Calcul de la valeur avec laquelle on vas corriger nos poids entre le hidden layer et le output layer
    output_layer_delta = output_layer_error * sigmoidPrime(output_layer)

    #Quels sont les poids entre l'input layer et le hidden layer qui ont  contribues a l'erreur, et dans quelle mesure?
    hidden_layer_error = np.dot(output_layer_delta, output_layer_weights.T)

    #Calcul de la valeur avec laquelle on vas corriger nos poids entre le input layer et le hidden layer
    hidden_layer_delta = hidden_layer_error * sigmoidPrime(hidden_layer)


    #Correction de nos poids
    output_layer_weights += np.dot(hidden_layer.T,output_layer_delta)
    hidden_layer_weights += np.dot(input_layer.T,hidden_layer_delta)

'''
    Phase de test
'''

# Propage nos informations a travers notre reseau de neurones.
input_layer = inputs_test
hidden_layer = sigmoid(np.dot(input_layer, hidden_layer_weights))
output_layer = sigmoid(np.dot(hidden_layer, output_layer_weights))

#Affiche le resultat
print("Test sur : ")
print(str(inputs_test))
print("------")
print("attendu : " + op)
print(str(T))
print("------")
print("resultat : ")
print(str(output_layer))


