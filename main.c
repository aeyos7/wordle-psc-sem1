#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_ATTEMPTS 6
#define WORD_LENGTH 5

// Word list - you can expand this with more words
const char *word_list[] = {
    "ABOUT", "ABUSE", "ACTOR", "ACUTE", "ADMIT", "ADOPT", "ADULT", "AFTER",
    "AGAIN", "AGENT", "AGREE", "AHEAD", "ALARM", "ALBUM", "ALERT", "ALIEN",
    "ALIKE", "ALIVE", "ALLOW", "ALONE", "ALONG", "ALTER", "ANGEL", "ANGER",
    "ANGLE", "ANGRY", "APART", "APPLE", "APPLY", "ARENA", "ARGUE", "ARISE",
    "ARRAY", "ARROW", "ASIDE", "ASSET", "AVOID", "AWAKE", "AWARD", "AWARE",
    "BADLY", "BAKER", "BASES", "BASIC", "BASIS", "BEACH", "BEGAN", "BEGIN",
    "BELOW", "BENCH", "BILLY", "BIRTH", "BLACK", "BLADE", "BLAME", "BLANK",
    "BLAST", "BLEED", "BLEND", "BLESS", "BLIND", "BLOCK", "BLOOD", "BOARD",
    "BOOST", "BOOTH", "BOUND", "BRAIN", "BRAND", "BRASS", "BRAVE", "BREAD",
    "BREAK", "BREED", "BRIEF", "BRING", "BROKE", "BROWN", "BUILD", "BUILT",
    "CABLE", "CALIF", "CARRY", "CATCH", "CAUSE", "CHAIN", "CHAIR", "CHALK",
    "CHAOS", "CHARM", "CHART", "CHASE", "CHEAP", "CHEAT", "CHECK", "CHESS",
    "CHIEF", "CHILD", "CHINA", "CHOSE", "CIVIL", "CLAIM", "CLASS", "CLEAN",
    "CLEAR", "CLICK", "CLIFF", "CLIMB", "CLOCK", "CLOSE", "CLOTH", "CLOUD",
    "COACH", "COAST", "COULD", "COUNT", "COURT", "COVER", "CRACK", "CRAFT",
    "CRASH", "CRAZY", "CREAM", "CRIME", "CRISP", "CROSS", "CROWD", "CROWN",
    "CRUDE", "CURVE", "CYCLE", "DAILY", "DAIRY", "DANCE", "DATED", "DEALT",
    "DEATH", "DEBUT", "DELAY", "DELTA", "DENSE", "DEPTH", "DERBY", "DETER",
    "DEVIL", "DICED", "DINER", "DINGY", "DIRTY", "DITCH", "DIVER", "DWELL",
    "DRAFT", "DRAMA", "DRANK", "DRAWN", "DREAM", "DRESS", "DRIED", "DRIFT",
    "DRILL", "DRINK", "DRIVE", "DROWN", "DRUNK", "DYING", "EAGER", "EAGLE",
    "EARLY", "EARTH", "EIGHT", "ELBOW", "ELDER", "ELECT", "ELITE", "EMPTY",
    "ENEMY", "ENJOY", "ENTER", "ENTRY", "EQUAL", "ERROR", "ERUPT", "ESSAY",
    "ETHIC", "EVENT", "EVERY", "EXACT", "EXERT", "EXILE", "EXIST", "EXTRA",
    "FACED", "FACET", "FACTS", "FAITH", "FALSE", "FAULT", "FAVOR", "FEAST",
    "FEATS", "FENCE", "FIBER", "FIELD", "FIERY", "FIFTH", "FIFTY", "FIGHT",
    "FILED", "FILER", "FILES", "FILLS", "FILMS", "FINAL", "FINCH", "FINDS",
    "FINED", "FINER", "FIRED", "FIRES", "FIRST", "FIXED", "FIXER", "FLAGS",
    "FLANK", "FLARE", "FLASH", "FLASK", "FLESH", "FLIER", "FLIES", "FLINT",
    "FLOAT", "FLOCK", "FLOOD", "FLOOR", "FLORA", "FLOUR", "FLOWN", "FLUID",
    "FLUKE", "FLUNG", "FLUSH", "FOAMY", "FOCAL", "FOCUS", "FOGGY", "FOLDY",
    "FOLKS", "FORCE", "FORGE", "FORMS", "FORTH", "FORUM", "FOUND", "FOYER",
    "FRAME", "FRANK", "FRAUD", "FREAK", "FREED", "FRESH", "FRIED", "FRIES",
    "FRILL", "FRISK", "FROGS", "FRONT", "FROST", "FROWN", "FRUIT", "FULLY",
    "FUNDS", "FUNGI", "FUNKY", "FUNNY", "FURRY", "FUSED", "FUZZY", "GAINS",
    "GALES", "GAMES", "GAMMA", "GANGS", "GATES", "GAUGE", "GAUGE", "GAVEL",
    "GEARS", "GEESE", "GENES", "GENRE", "GHOST", "GIANT", "GIFTS", "GIRLS",
    "GIVEN", "GIVER", "GIVES", "GLASS", "GLAZE", "GLEAN", "GLEAM", "GLIDE",
    "GLINT", "GLOBE", "GLOOM", "GLORY", "GLOSS", "GLOZE", "GLUED", "GLYPH",
    "GOATS", "GOING", "GOLLY", "GOODS", "GOOEY", "GOOSE", "GRACE", "GRADE",
    "GRAFT", "GRAIN", "GRAND", "GRANT", "GRAPE", "GRASP", "GRASS", "GRATE",
    "GRAVE", "GRAVY", "GRAZE", "GREAT", "GREED", "GREEN", "GREET", "GRIEF",
    "GRILL", "GRIME", "GRIMY", "GRIND", "GRINS", "GRIPE", "GRIST", "GRITS",
    "GROAT", "GROOM", "GROPE", "GROSS", "GROUP", "GROUT", "GROVE", "GROWL",
    "GROWN", "GROWS", "GRUEL", "GRUFF", "GRUNT", "GUARD", "GUESS", "GUEST",
    "GUIDE", "GUILD", "GUILT", "GUISE", "GULCH", "GULLS", "GULPS", "GUMMY",
    "GURUS", "GUSTS", "GUTSY", "HABIT", "HAILS", "HAIRS", "HALLS", "HALTS",
    "HANDS", "HANDY", "HANGS", "HAPPY", "HARDY", "HASTE", "HASTY", "HATCH",
    "HATED", "HATER", "HATES", "HAULS", "HAUNT", "HAVEN", "HAVOC", "HAWKS",
    "HAZEL", "HEADS", "HEALS", "HEAPS", "HEARD", "HEARS", "HEART", "HEATH",
    "HEATS", "HEAVY", "HEDGE", "HEELS", "HEIRS", "HEIST", "HELIX", "HELLO",
    "HELPS", "HENCE", "HERBS", "HERDS", "HERON", "HIDES", "HIGHS", "HILLS",
    "HILTS", "HINDS", "HINGE", "HINTS", "HIPPO", "HIRED", "HIRES", "HOBBY",
    "HOIST", "HOLDS", "HOLES", "HOLLY", "HOODS", "HOOFS", "HOOKS", "HOOPS",
    "HOOTS", "HOPED", "HOPES", "HORNS", "HORNY", "HORSE", "HOSED", "HOSES",
    "HOTEL", "HOUND", "HOURS", "HOUSE", "HOVEL", "HOVER", "HOWLS", "HUBS",
    "HUFFS", "HUFFY", "HULKS", "HULLS", "HUMAN", "HUMID", "HUMOR", "HUMPS",
    "HUMUS", "HUNKS", "HUNTS", "HURLS", "HURRY", "HURTS", "HUSKS", "HYDRO",
    "HYENA", "HYMNS", "HYPES", "IDEAL", "IDEAS", "IDIOM", "IDIOT", "IDLED",
    "IDLES", "IDYLL", "IFRIT", "IGLUS", "IGNORE", "ILIAC", "IMAGE", "IMAGO",
    "IMBED", "IMBUE", "IMMIX", "IMPED", "IMPEL", "IMPLY", "IMPOS", "IMPRO",
    "IMPUD", "IMPUR", "INANE", "INAPT", "INARM", "INARY", "INBAR", "INBAY",
    "INBID", "INBOW", "INBOX", "INCAP", "INCAS", "INCLE", "INCOG", "INCUT",
    "INDEW", "INDEX", "INDIA", "INDIE", "INDOL", "INDRI", "INDUS", "INFER",
    "INFIT", "INFRA", "INGLE", "INGOT", "INGRA", "INGRH", "INGRI", "INGUL",
    "INHAN", "INHAY", "INHED", "INHER", "INHEY", "INHIB", "INIA", "INIAC",
    "INIAL", "INION", "INJAM", "INJAV", "INJOY", "INJUN", "INJUR", "INKAH",
    "INKER", "INKIE", "INKLE", "INKED", "INKING", "INKLE", "INKPOT", "INKY",
    "INLAY", "INLET", "INNER", "INNIT", "INNLY", "INNIE", "INOCH", "INOCK",
    "INODE", "INOGA", "INOGY", "INOIL", "INOKE", "INOLA", "INOLE", "INOLY",
    "INOMA", "INOME", "INOMY", "INONE", "INONY", "INOOB", "INOOK", "INOOL",
    "INOOM", "INOON", "INOOO", "INOOP", "INOOR", "INOOS", "INOOT", "INOOU",
    "INOOV", "INOOZE", "INOZO", "INPUT", "INQUE", "INRAD", "INRAS", "INRAT",
    "INRAW", "INRAY", "INRED", "INRES", "INRET", "INREV", "INREW", "INREY",
    "INREZ", "INRIB", "INRID", "INRIE", "INRIG", "INRIN", "INRIO", "INRIP",
    "INRIS", "INRIT", "INRIX", "INRIY", "INRIZ", "INROB", "INROD", "INROE",
    "INROG", "INROH", "INROK", "INROL", "INROM", "INRON", "INROO", "INROP",
    "INROS", "INROT", "INROU", "INROV", "INROW", "INROX", "INROY", "INROZ"
};

// Color codes for terminal output
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define GRAY "\x1b[90m"
#define RESET "\x1b[0m"
#define BOLD "\x1b[1m"

typedef struct {
    char letter;
    int status;  // 0 = gray, 1 = yellow, 2 = green
} LetterStatus;

void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

int is_valid_word(const char *word) {
    if (strlen(word) != WORD_LENGTH) {
        return 0;
    }
    for (int i = 0; i < strlen(word_list) / sizeof(word_list[0]); i++) {
        if (strcmp(word, word_list[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

LetterStatus *check_guess(const char *guess, const char *target) {
    LetterStatus *result = (LetterStatus *)malloc(WORD_LENGTH * sizeof(LetterStatus));
    
    // First pass: mark greens and set status
    for (int i = 0; i < WORD_LENGTH; i++) {
        result[i].letter = guess[i];
        if (guess[i] == target[i]) {
            result[i].status = 2;  // Green - correct position
        } else {
            result[i].status = 0;  // Default to gray
        }
    }
    
    // Second pass: mark yellows
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (result[i].status == 0) {  // Not green
            for (int j = 0; j < WORD_LENGTH; j++) {
                if (i != j && guess[i] == target[j] && result[j].status != 2) {
                    result[i].status = 1;  // Yellow - wrong position
                    break;
                }
            }
        }
    }
    
    return result;
}

void print_guess_result(LetterStatus *result) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (result[i].status == 2) {
            printf("%s%c%s ", GREEN, result[i].letter, RESET);
        } else if (result[i].status == 1) {
            printf("%s%c%s ", YELLOW, result[i].letter, RESET);
        } else {
            printf("%s%c%s ", GRAY, result[i].letter, RESET);
        }
    }
    printf("\n");
}

void print_header() {
    printf("\n");
    printf("%s=======================%s\n", BOLD, RESET);
    printf("%s     WORDLE GAME%s\n", BOLD, RESET);
    printf("%s=======================%s\n", BOLD, RESET);
    printf("\nGuess the word in %d attempts!\n\n", MAX_ATTEMPTS);
    printf("Color hints:\n");
    printf("  %sGREEN%s = Correct letter, correct position\n", GREEN, RESET);
    printf("  %sYELLOW%s = Correct letter, wrong position\n", YELLOW, RESET);
    printf("  %sGRAY%s = Letter not in word\n\n", GRAY, RESET);
}

int main() {
    srand(time(NULL));
    
    // Pick a random word
    int word_count = sizeof(word_list) / sizeof(word_list[0]);
    const char *target_word = word_list[rand() % word_count];
    
    print_header();
    
    char guess[WORD_LENGTH + 1];
    int attempts = 0;
    int won = 0;
    
    while (attempts < MAX_ATTEMPTS) {
        printf("%sAttempt %d/%d: %s", BOLD, attempts + 1, MAX_ATTEMPTS, RESET);
        
        // Get user input
        if (fgets(guess, sizeof(guess), stdin) == NULL) {
            break;
        }
        
        // Remove newline
        if (guess[strlen(guess) - 1] == '\n') {
            guess[strlen(guess) - 1] = '\0';
        }
        
        to_uppercase(guess);
        
        // Validate input
        if (strlen(guess) != WORD_LENGTH) {
            printf("%sError: Word must be exactly %d letters long.%s\n\n", BOLD, WORD_LENGTH, RESET);
            continue;
        }
        
        int valid = 1;
        for (int i = 0; i < WORD_LENGTH; i++) {
            if (!isalpha(guess[i])) {
                valid = 0;
                break;
            }
        }
        
        if (!valid) {
            printf("%sError: Word must contain only letters.%s\n\n", BOLD, WORD_LENGTH, RESET);
            continue;
        }
        
        // Check the guess
        LetterStatus *result = check_guess(guess, target_word);
        print_guess_result(result);
        free(result);
        
        attempts++;
        
        // Check if won
        if (strcmp(guess, target_word) == 0) {
            won = 1;
            break;
        }
        
        printf("\n");
    }
    
    // Print result
    printf("\n%s=======================%s\n", BOLD, RESET);
    if (won) {
        printf("%sYOU WON!%s\n", GREEN, RESET);
        printf("%sWord: %s%s\n", BOLD, target_word, RESET);
        printf("%sAttempts: %d/%d%s\n", BOLD, attempts, MAX_ATTEMPTS, RESET);
    } else {
        printf("%sGAME OVER%s\n", BOLD, RESET);
        printf("%sWord was: %s%s\n", BOLD, target_word, RESET);
    }
    printf("%s=======================%s\n", BOLD, RESET);
    printf("\nThanks for playing!\n\n");
    
    return 0;
}
