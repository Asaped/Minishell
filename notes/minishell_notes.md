# MINISHELL

## Liste des fonctions autorisees :

[//]: <Fonctions de prompts>
**```char *readline(const char *prompt);```**
Simplement, cette fonction lie et recupere l'input de l'user, pour le retourner en string. Peut afficher un prompt ```const char *prompt```.
- le ```*prompt``` est facultatif : c'est le prompt affiché en attendant l'entree utilisateur.
- elle retourne en string (mallocé !!, donc a free absolument) l'entree utilisateur. Peut retourner ```NULL``` si l'user fais cmd+D OU la string est vide OU échec de parse.
- ```#include <readline/readline.h>```
- A compiler avec ```-lreadline``` !!!
> Remarque: Peut leak. Attention a l'usage.

---

[//]: <Les fonctions wait: Attente de fin de process enfants.>
**```pid_t wait(int *status);```**
Suspend l'exécution du processus parent jusqu'à ce que UN DES processus enfants se termine. 
- Retourne le PID de l'enfant qui s'est terminé.
- Si le processus parent a plusieurs enfants, retourne le PID du premier enfant qui se termine.
- Le statut de sortie de l'enfant se trouve dans la variable status.
- ```#include <sys/wait.h>```

**```pid_t waitpid(pid_t pid, int *status, int options);```**
Suspend l'exécution du processus parent jusqu'à ce qu'un processus enfant spécifique se termine.
- Retourne le pid de l'enfant qui a terminé
- ```int *status``` permet de savoir a quel status l'enfant a termine le process.
- possible d'ajouter des options avec ```int *options```. voir man pour les exemples.
- ```#include <sys/wait.h>```

---

[//]: <Les fonctions de signaux.>
**```void (*signal(int signum, void (*handler)(int)))(int);```**
Fonction pour gerer l'entree d'un signal.
- ```signum``` est le int correspondant au signal recu :
	- SIGINT = ctrl+C
	- SIGQUIT = ctrl+\ - fin d'un process avec core dump, mais ne doit rien faire pour minishell /!\
	- SIGTERM = demande la terminaison d'un process proprement (UTILE !)
	- SIGUSR1 et SIGUSR2 = signaux utilisateurs persos, envoie de signau entre process (enfant/parent, enfant/enfant)
- ```#include <signal.h>```

**```int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);```**
Version + pousee et precise de ```signal()``` pour gerer l'entree d'un signal.
- ```signum``` est le int correspondant au signal recu : comme ```signal()```
- ```*act``` pointeur vers une ```struct sigaction``` qui specifie un nouveau comportement associe au signal recu
- ```oldact``` la ```struct sigaction``` precedente ou l'ancien comportement est stocké, ou NULL si non definie au prealable. (Pas forcement utile dans le cas de MS)
La struct sigaction :
```
struct sigaction {
    void (*sa_handler)(int);     // Pointeur vers le gestionnaire de signal personnalisé
    void (*sa_sigaction)(int, siginfo_t *, void *);  // Pointeur vers une fonction de gestionnaire de signal (utilisé avec SA_SIGINFO)
    sigset_t sa_mask;            // Ensemble de signaux à bloquer lors de l'exécution du gestionnaire
    int sa_flags;                // Options et drapeaux (par exemple, SA_RESTART)
    void (*sa_restorer)(void);   // Fonction de restauration du contexte (utilisé avec SA_SIGINFO)
};
```

**```int kill(pid_t pid, int sig);```**
Permet d'envoyer un signal a un process specifique, ou a un groupe de process.
- ```pid``` le pid du process a qui envoyer le signal
- ```sig``` le signal a envoyer a pid
- Retourne 0 si succes, ou -1 si erreur.
- ```#include <signal.h>```

[//]: <Les fonctions de chemins/fichiers.>
**```char *getcwd(char *buf, size_t size);```**
Recupere sous forme de string le chemin absolu où le process s'execute. (UTILE !)
- ```*buf``` Le buffer ou la chemin sera stocké
- ```size``` La taille du buffer
- Retourne le buffer *buf passe en argument qui contient le chemin absolu, ou NULL si erreur.
- ```#include <unistd.h>```

**```int chdir(const char *path);```**
Permet de changer le repertoire courant du process en cours d'execution. (UTILE !)
- ```*path``` buffer du repertoire de destination, peut etre absolu ou relatif
- retourne 0 si succes, sinon -1
- ```#include <unistd.h>```

**```int unlink(const char *pathname);```**
Supprime un fichier specifié par pathname (par un chemin absolu ou relatif)
- ```*pathname``` le nom du fichier avec ou non le chemin a supprimer
- retourne 0 si succes, sinon -1
- ```#include <unistd.h>```

##### IMPORTANT
**```int execve(const char *filename, char *const argv[], char *const envp[]);```**
Execute un fichier. a utilisee avec un fork() pour eviter de fermer le programme, car il ne creer pas de nouveaux process ! (A voir : peut etre ajouter une fonction (1) qui lance execve() en creant tout seul un nouveau process)
- ```*filename``` nom du fichier a executer avec ou non le chemin absolu ou relatif
- ```*argv[]``` les arguments a passer a ce fichier. Le dernier element est null afin d'indiquer la fin du tableau
- ```*envp[]``` des variables d'environnement Le dernier element est null afin d'indiquer aussi la fin du tableau
Exemple de fonction pour execve() avec une fork() d'office
```
int safe_execve(const char *program_path, char *const program_argv[], char *const program_envp[])
{
    pid_t	pid; 
	int status;

	pid = fork(); // Crée un processus fils
	if (pid < 0)
        return (-1);
    if (pid == 0) // Code exécuté dans le processus fils
	{
        if (execve(program_path, program_argv, program_envp) == -1)
            return (-1);
    }
	else // Code exécuté dans le processus parent
	{
        if (wait(&status) == -1)
            return (-1);
        if (WIFEXITED(status))
            return WEXITSTATUS(status); // Renvoie le code de retour du processus fils
        else
            return (-1);
    }
    return (0);
}
```

**```int dup(int oldfd)```** & **```int dup2(int oldfd, int newfd);```**
Duplique un descripteur de fichier. Une fois lancée, toutes les opérations qui se feront sur le ```oldfd``` seront aussi appliquées sur le ```newfd```. Comme une sorte de syncornisation de fd, pour que oldfd et newfd soient liés,et que les modifications sur l'une se feront aussi sur l'autre. Pour dup() simple, elle prends le plus bas fd disponible après duplication
- ```oldfd``` ancien file descriptor
- ```newfd``` destination du nouveau file descriptor, auquel sera appliqué maintenant toutes les operations faites sur oldfd (seulement pour dup2(), dup() prends seulement en parametre le oldfd)
- return le newfd si elle reussit, -1 si erreur.

**```int pipe(int pipefd[2]);```**
Creer un tunnel de communication entre 2 process (parent et fils) après un fork(). 
- ```pipefd[0]``` est pour fait pour la lecture (vrai nom: read end)
- ```pipefd[1]``` est pour fait pour l'ecriture (vrai nom: write end)
Ces 2 passages sont valables pour les 2 process, c'est a dire que l'un et l'autre ont acces a l'ecriture comme a la lecture. Attention a la syncronisation, absolument utiliser des signaux pour avertir le parent que le fils a terminer, pour ensuite lire l'output du tunnel du fils, ou vice-versa.
> exemple : Le processus parent doit fermer pipefd[0] (lecture) s'il écrit dans pipefd[1] (écriture), et le processus fils doit fermer pipefd[1] s'il lit depuis pipefd[0].

---

[//]: <Les fonctions des dossiers.>
**```DIR *opendir(const char *pathname);```**
Ouvre le dossier ```*pathname``` (sous forme de chemin absolu ou relatif). ```DIR``` correspond a une structure. Cette structure est opaque, on a donc pas acces aux informations a l'interieur, mais ce n'est pas necessaire car on peut acceder directement aux dossiers via les fonctions ```readdir()```.
- ```*pathname``` comme mentionné, soit un chemin absolu, soit un chemin relatif
- return la struct si succes, sinon retourne NULL
- ```#include <unistd.h>```
> Remarque : un peu similaire a open(), dans le sens ou elle ne fait qu'ouvrir le dossier mentionné. Ne pas oublie de closedir() des que necéssaire.

**```struct dirent *readdir(DIR *dirp);```**
Lis le premier fichier et/ou sous-dossier d'un dossier DIR ouvert par la fonction ```opendir()```
- ```DIR *dirp``` resultat de la fonction ```opendir()```, et donc les fichiers et dossiers a lire.
- ```struct dirent*``` retour de la fonction: une structure. Elle est constituée de la facon suivante : 
```
struct dirent {
    ino_t d_ino;         // Numéro d'inode (structure contenant permissions, dates, taille...etc)
    off_t d_off;         // Offset pour la prochaine readdir() (pas utile dans notre cas)
    unsigned short d_reclen; // Longueur de cet enregistrement (taille de la liste, combien ya til de fichiers et dossiers)
    unsigned char d_type; // Type du fichier (DT_REG = fichier regulier, DT_DIR = dossier, DT_FIFO = tube, etc.)
    char *d_name;       // Nom du fichier ou du sous-répertoire
};
```
- ```#include <unistd.h>```
En soit, la fonciton retourne une struct comprenant toute les infos du premier dossier/fichier lu.
Un peu de la meme maniere que GNL, on appelle la fonction jusqu'a qu'elle renvoie NULL pour avoir tout les dossiers et fichiers du dossier recuperé par opendir(). Peut etre utile pour comparer l'input de l'user et verifier qu'il est valide.
> Remarque : Ne pas oublier de closedir() des que necéssaire.

---

[//]: <Les fonctions d'erreurs.>
**```char *strerror(int errnum);```**
Transforme le code d'erreur ```errno``` en chaine de caractere lisibile et comprehensible pour un humain. Le message d'erreur est le message par défaut du systeme. Peut etre interpreté (comme elle retourne un char*)
- ```errnum``` code renvoyé par ```errno``` errno est variable globale, pas une fonction.
- return la string de l'erreur correspondante.
- ```#include <string.h>```

**```void perror(const char *s);```**
Imprime un message d'erreur personnalisé, utile pour le debug.
- ```*s``` Le message d'erreur a print.
- Pas de return, elle ecrit simplement l'erreur.
- ```#include <stdio.h>```

[//]: <Les fonctions d'identification du terminal. (pas utile dans notre cas je pense)>
```#include <unistd.h>```
isatty = Si le fd passe en parametre est bien un terminal, si OK: retourne 1, sinon 0
ttyname = Si le fd passe en parametre est bien un terminal, si OK: retourne le nom du terminal en char *str, sinon NULL
ttyslot = recuperer le numero du terminal, si OK: return le numero du terminal, sinon -1

[//]: <Les fonctions de config/customization du terminal. (pas utile dans notre cas je pense)>
tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs... etc. Toutes pour personnaliser ou configurer le terminal. Pourra etre utile pour personnaliser les couleurs du shell etc, mais pour le moment, pas d'utilité

## A SAVOIR

###### Variables d'environnements (venv)

Il faut absolument recuperer toutes les variables d'environnement lors du lancement du programme, et les initialiser dans une structure par ex, afin qu'elle puisse etre modifiee uniquement dans le programme, et garder les originaux la ou elles sont.
Ca peut se faire avec la variable globale ```extern char **environ```. Ce tableau de string contient toutes les variables globales. On peut les stocker en liste chainees de cette facon : 
```
typedef struct	s_venv
{
	char			*name;
	char			*value;
	struct s_venv	*next;
}				t_venv;
```
Remarque : La venv SHLVL doit etre incrementée de 1 a chaque parse. Elle correponds aux couches de terminal. Moyens memotechnique pour s'en souvenir: le nombre de fois l'on doit taper exit pour quitter le terminal. Pourquoi ? Parce quon peut lancer minishell dans minishell, et encore et encore... etc.