textMining
==========

Spellchecker with Damerau–Levenshtein distance

Ce projet a été réaliser en C++2011 (utilisation de G++). Pour sa compilattion,
il suffit de suivre la procédure suivante:

./configure && make

Des commandes suplémentaires ont été ajouté au Makefile:
    -> clean
    -> distclean
    -> doc

L'usage des ces deux outils est simple. Il faut fournir un fichier text (dico)
sous la forme suivante au compilateur.

     word1 10 <- ce chiffre correspond à la fréquence du mot
     word2 20
     ...

                 /!\ Attention /!\
Il ne doit pas y avoir des lignes vide dans le fichier.

Le compilateur va donc générer un fichier binaire qui est votre dico sous une
autre forme (Patricia Trie compilé).

Usage pour le compilateur: ./TextMiningCompiler file_in file_ou

Une fois cette première étape réalisé, pour calculer les distances voulus par
rapport à un mot, il suffit d'appeler le second applicatif.

Usage pour l'interpréteur:
      Test unitaire ->  echo "approx 2 mot" | ./TextMiningApp file_in (dico compilé)
      Tests multiples -> cat testFile | ./TextMiningApp file_in (dico compilé)

Questions:
==========

 1. Decrivez les choix de design de votre programme
    
    Nous avons en premier lieu choisi de sérializer "à la main" notre structure
    de donnée compilée à l'aide de mmap(). En effet, après avoir essayer
    boost::serialization, nous avons réalisé que c'était le seul moyen d'avoir
    de bonnes performances de chargement pour l'interpréteur.
    
    Cela nous a de plus permis de créer un structure de données très "packée"
    qui permet une meilleure utilisation du cache et moins de page faults. De
    plus l'optimisation de l'espace est très bonne. Avec le dictionnaire fourni,
    l'interpréteur n'a besoin que de 120Mo de RAM pour fonctionner.

    Enfin, nous utilisons un Bloom filter qui nous permet d'améliorer les
    performances pour les distances de 0.

 2. Listez l'ensemble des tests effectués sur votre programme (en plus des units tests)

    Afin de couvrir un maximum de cas "tricky" possibles il a été indispensable
    de générer une base de requêtes variée.

    Nous avons aussi crée nos propres dictionnaires de mots générés aléatoirement pour
    tester le plus de mots possibles face à la ref.

    De plus, nous avons testé sur des machines 32-bits et 64-bits pour nous
    assurer que les tailles des types de base n'interféraient pas avec notre
    sérialization (et nous avons bien fait car cela plantait pas mal).

    Pour profiler, nous avons utilisé gprof.

    Enfin, pour surveiller la RAM, c'était avec les yeux et 'htop' et nous nous
    sommes vite rendu compte que nous n'étions pas particulièrement inquiétés
    par cette contrainte.

 3. Avez-vous détecté des cas où la correction par distance ne fonctionnait pas (même avec une distance  élevée) ?

    Non. Cependant, à ce sujet, afin de savoir si un préfix a le potentiel
    d'avoir un mot dont la distance est correcte parmis ses fils, nous utilisons
    la plus longue sous séquence commune (LCS) de caractères entre ce préfix et
    le mot recherché. Ainsi, si la LCS compense une distance importante, alors
    nous savons qu'il est utile d'aller voir les fils de ce prefix.

 4. Quelle est la structure de données que vous avez implémentée dans votre projet, pourquoi ?

    Nous avons implémenté un Patricia Trie compilé. Les raisons sont que les
    dictionnaires de moins de 15 millions de mots tiennent dans 512Mo de RAM
    avec notre implémentation. Aussi, l'utilisation du cache est bonne et nous
    évitons les IO couteuses avec le disque dur.

    Un Bloom filter est aussi utilisé en surcouche.

 5. Proposez un réglage automatique de la distance pour un programme qui prend juste une chaîne de caractères en entrée, donner le processus d'évaluation ainsi que les résultats

    Une bonne approche serait probablement d'adapter la distance à la taille du
    mot. Plus le mot est grand et plus la taille augmente car il peut y avoir de
    plus en plus de fautes dans un même mot.
    Les résultats sont triés comme ici, par distance, fréquence puis ordre
    lexicographique.

 6. Comment comptez vous améliorer les performances de votre programme

    Nous n'avons malheureusement pas eu le temps de nous pencher sur
    l'amélioration des performances.
    Nous aurions probablement essayé d'améliorer la fonction de calcul de
    distances qui occupe 80% du temps de notre programme.
    Peut-être aurions-nous pu aussi optimiser le parcours du patricia trie en
    regardant l'utilisation du cache.

    La programmation dynamique pourrait aussi être utile au cas où une requête
    reviendrait souvent. En plus nous avons assez de RAM pour le faire.

 7. Que manque-t-il à votre correcteur orthographique pour qu'il soit à l'état de l'art ?

    Il manque une gestion de tags donnant la nature et la fonction des mots du
    dictionnaire ainsi qu'une analyse de la phrase dans laquelle se trouve le
    mot à l'aide de chaînes de Markov cachées. Ainsi, si l'on sait que le mot
    sur lequel la faute a été faite est censé être un verbe, on peut proposer
    une correction par un verbe en priorité.

    La gestion de plusieurs langages est aussi important (un set de
    dictionnaires par langage probablement).
