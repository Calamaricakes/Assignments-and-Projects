module Proj1 (Person, parsePerson, height, hair, sex, GameState, initialGuess,
              nextGuess, feedback) where

-- Declarative Programming, Semester 2, Project 1
-- Name: Lai Nge Nern, Student Number: 639702

import Data.List

-- START Data type declarations

--A Person is comprised of their Height, HairColour, and Gender
data Person = Person { tallness :: Height
                     , hairColour :: HairColour
                     , sex :: Gender
                     } deriving (Eq, Show)

data Height = Short | Tall
    deriving (Eq, Show, Enum, Ord)

data HairColour = Blonde | Dark | Red
    deriving (Eq, Show, Enum, Ord)

data Gender = Male | Female
    deriving (Eq, Show, Enum, Ord)

-- GameState has:
--  the first list as the remaining lineups after processing
--  the second is to keep track of lineups already guessed
data GameState = GS [[Person]] [[Person]]
    deriving Show

data InfoPack = IP [Height] [HairColour] [Gender]

data LineUpFeatureSets = FS [Height] [HairColour] [Gender]
    deriving Show

data CharacteristicSets = CS HeightSet HairColourSet GenderSet
    deriving Show

-- list of height combinations
data HeightSet = HT [ [Height] ]
    deriving Show

-- list of hairColour combinations
data HairColourSet = HC [ [HairColour] ]
    deriving Show

-- list of gender combinations
data GenderSet = G [ [Gender] ]
    deriving Show

-- END Data type declarations

-- START Parsing input characters into their appropriate types for Person

parsePerson :: String -> Maybe Person
parsePerson [] = error "No input"
parsePerson (height: hairColour: gender: extra)
    | length (height: hairColour: gender: extra) /= 3
        = error "Incorrect input."
    | otherwise
        = Just (Person (parseHeight height)
                 (parseHairColour hairColour)
                 (parseGender gender))

parseHeight :: Char -> Height
parseHeight height
    | height == 'S' = Short
    | height == 'T' = Tall
    | otherwise     = error "Incorrect height input."

parseHairColour :: Char -> HairColour
parseHairColour hairColour
    | hairColour == 'B' = Blonde
    | hairColour == 'D' = Dark
    | hairColour == 'R' = Red
    | otherwise         = error "Incorrect hair colour input."

parseGender :: Char -> Gender
parseGender gender
    | gender == 'M' = Male
    | gender == 'F' = Female
    | otherwise     = error "Incorrect gender input."

-- END Parsing input characters into their appropriate types for Person

--
-- INPUTS ARE NOW ASSUMED TO BE IN CORRECT FORMAT, END ERROR HANDLING
--

-- START Data extraction functions

-- Gets the height of a person
height :: Person -> Height
height (Person headDistanceFromGround _ _) = headDistanceFromGround

-- Gets the hairColour of a person
hair :: Person -> HairColour
hair (Person _ hairColour _) = hairColour

-- Gets the gender of a person
gender :: Person -> Gender
gender (Person _ _ sex) = sex

-- Gets all the characteristics present for a particular lineup, and puts
-- them in LineUpFeatureSets
extractCharacteristics :: [Person] -> LineUpFeatureSets
extractCharacteristics p =
    let heightInfo = map height p
        colourInfo = map hair   p
        genderInfo = map gender p
    in
    FS heightInfo colourInfo genderInfo

extractHeights :: InfoPack -> [Height]
extractHeights (IP ht _ _) = ht

extractHairColours :: InfoPack -> [HairColour]
extractHairColours (IP _ hc _) = hc

extractGenders :: InfoPack -> [Gender]
extractGenders (IP _ _ sex) = sex

extractCurrentHeightSet :: [Person] -> [Height]
extractCurrentHeightSet [] = []
extractCurrentHeightSet (p:ps)
    = height p : extractCurrentHeightSet ps

extractCurrentHairColourSet :: [Person] -> [HairColour]
extractCurrentHairColourSet [] = []
extractCurrentHairColourSet (p:ps)
    = hair p : extractCurrentHairColourSet ps

extractCurrentGenderSet :: [Person] -> [Gender]
extractCurrentGenderSet [] = []
extractCurrentGenderSet (p:ps)
    = gender p : extractCurrentGenderSet ps

-- END Data extraction functions


-- START Char outputs for Person characteristics

heightChar :: Height -> Char
heightChar headDistanceFromGround
    | headDistanceFromGround == Short = 'S'
    | headDistanceFromGround == Tall  = 'T'

hairColourChar :: HairColour -> Char
hairColourChar colour
    | colour == Blonde = 'B'
    | colour == Dark   = 'D'
    | colour == Red    = 'R'

genderChar :: Gender -> Char
genderChar sex
    | sex == Male   = 'M'
    | sex == Female = 'F'

-- Takes a Person's characteristics and converts it into a string
personString :: Person -> String
personString (Person headDistanceFromGround hairColour sex)
    = [(heightChar headDistanceFromGround),
       (hairColourChar hairColour        ),
       (genderChar sex                   )]

-- END Char outputs for Person characteristics

-- START Guess logics

-- Compare the culprits with current line up of two Persons

feedback :: [Person] -> [Person] -> (Int, Int, Int, Int)

-- feedback function which returns the score of the current guess
-- compared to the culprits. The scores are calculated as the number
-- of matching features that are in the lineUp compared to the
-- culprits

feedback culprits lineUp =


    let (new_c, new_l) = rPF culprits lineUp -- remove perfect matches
        culpritLooks   = gCS new_c           -- get culprit features
        lineUpLooks    = gCS new_l           -- get lineup  features
    in
    (  nPM culprits lineUp                          --  Num perfect match
     , count (eH culpritLooks)  (eH lineUpLooks )   --  height      score
     , count (eHC culpritLooks) (eHC lineUpLooks)   --  hair colour score
     , count (eG culpritLooks)  (eG lineUpLooks )   --  gender      score
    )
    where
        rPF  = removePerfectMatches
        gCS  = generateCharacteristicSet
        nPM  = numPerfectMatch
        eH   = extractHeights
        eHC  = extractHairColours
        eG   = extractGenders


count :: Eq a => [a] -> [a] -> Int

-- Score counter:
--    - checks if an element l is in l2,
--          - if it is then add 1, then remove l that is in l2
--          - else continue with the rest of elements in ls
--          - recur until ls is empty

count [] _ = 0
count (l:ls) l2
    | elem l l2 = 1 + count ls (delete l l2)
    | otherwise = count ls l2

generateCharacteristicSet :: [Person] -> InfoPack

-- Gets all the characteristics from a list of Persons

generateCharacteristicSet persons = IP
    (map height persons)
    (map hair   persons)
    (map gender persons)

removePerfectMatches :: [Person] -> [Person] -> ([Person], [Person])

-- remove correct guesses currently in the lineup, then output the
-- new list as a tuple

removePerfectMatches culprits lineUp
    = (culprits \\ lineUp, lineUp \\ culprits)


numPerfectMatch :: [Person] -> [Person] -> Int

-- counts the number of Persons that are perfect matches to the guess

numPerfectMatch p1 p2 = length [ x | x <- p1, y <- p2, x == y]

initialGuess :: ([Person], GameState)

-- Initial guess would be "SBM" and "SDM" to eliminate. This allows us to
-- determine the current set of features in Height and Gender.
-- For example: score of 0: No Male features in culprits,
--                          therefore has to be the set of two females
--                       1: Currently 1 male culprit,
--                          therefore the other has to be female
--                       2: Both male culprits
-- The same can be done for gender.
-- hair colour is non-binary and requires more logic to compute.

initialGuess =
    let p1 = Person Short Blonde Male
        p2 = Person Short Dark Male
        currentLineUp = generateAllLineups
    in

    -- [p1,p2]                : current guess
    -- GS currentLineUp [[]]) :
    --    currentLineUp - all possible lineups
    --             [[]] - currently no guesses with feedback so empty list

    ([p1,p2], GS currentLineUp [[]])

nextGuess :: ([Person], GameState) -> (Int, Int, Int, Int) ->
             ([Person], GameState)

-- nextGuess takes the last guess that was made and returns another guess
-- based on the feedback (quad element tuple) received.

-- first, the scores, last guess made, and the remaining candidates
--        are sent to be processed by scoringInterpretationHeightAl
--        which removes candidates that do not match the current height
--        features resulting in the list matchingHeight
--
-- second,matchingHeight is then processed by
--        scoringInterpretationGenderAl which removes candidates that do
--        not match the current gender features, resulting in
--        matchingGender
--
-- then  ,matchingGender is processed by scoringInterpretationColourAl
--        which removes candidates that do not match the current hair
--        colour features, resulting in matchingPersons.
--
-- matchingPersons is a list of lineups that match the current set of
-- features which is the height, haircolour, and gender. However, it does
-- not account for the particular combination the features are in.
-- So, it is necessary to have a 'guessed' list to ensure that each guess
-- is unique.
--
-- Finally   , we take the head of matchingPersons as our next guess
--           , add the guess to our list of guessed candidates
--           , then repeat until the correct guess is obtained.

nextGuess (lastGuess, GS remaining guessed)
          (perfectMatchScore, heightScore, hairScore, genderScore)

    -- if the current guess has been guessed before
    | elem currentGuess guessed = nextGuess
        ( lastGuess,
          GS (delete currentGuess remaining) (currentGuess : guessed))
        ( perfectMatchScore, heightScore, hairScore, genderScore )

    | otherwise =
        (currentGuess,
        GS matchingPersons
        (currentGuess : guessed))

    where matchingHeight =
            scoringInterpretationHeightAl
                (perfectMatchScore, heightScore) lastGuess remaining

          matchingGender =
            scoringInterpretationGenderAl
                (perfectMatchScore, genderScore) lastGuess matchingHeight

          matchingPersons =
            scoringInterpretationColourAl
                (perfectMatchScore, hairScore) lastGuess matchingGender

          currentGuess = (head matchingPersons)


removeCurrentCombinationFromList :: Eq a => [a] -> [[a]] -> [[a]]

-- remove lineups that contain the current candidates in the list

removeCurrentCombinationFromList _ [] = []
removeCurrentCombinationFromList c (c1:cs)
    | inList c c1  = removeCurrentCombinationFromList c cs
    | otherwise    = c1 : removeCurrentCombinationFromList c cs

removeCurrentCombinationNotFromList :: Eq a => [a] -> [[a]] -> [[a]]

-- remove the lineUps that do not have current candidates in the list

removeCurrentCombinationNotFromList _ [] = []
removeCurrentCombinationNotFromList c (c1:cs)
    | not (inList c c1) = removeCurrentCombinationFromList c1 cs
    | otherwise         = c1 : removeCurrentCombinationFromList c cs

scoringInterpretationHeightAl ::
    (Int, Int) -> [Person] -> [[Person]] -> [[Person]]

-- the filtering algorithm to remove lineUps that do not match the
-- current height features.

scoringInterpretationHeightAl (pm, s) lineUp rm

    -- remove lineUps that have candidates in the list
    -- remove lineUps that have the same heights as in the list
    | pm == 0 && s == 0 = rM

    -- remove lineUps that do not have at least one of the heights
    -- in the list
    | pm == 0 && s == 1 =
        removeCombinationsWithoutAnyHeight currentHeightSet rm

    -- remove lineUps that do not have the exact same heights as the
    -- list
    | pm == 0 && s == 2 =
        removeCombinationsWithoutHeight currentHeightSet rm

    -- remove lineUps that have the exact combination of heights
    | pm == 1 && s == 0 =
        removeParticularHeightCombination currentHeightSet rm

    -- remove combinations that do not have the exact same heights as
    -- in the list
    | pm == 1 && s == 1 =
        removeCombinationsWithoutHeight currentHeightSet rm

    where currentHeightSet = extractCurrentHeightSet lineUp
          rH = removeCombinationsWithHeight currentHeightSet rm
          rM = removeCurrentCombinationFromList lineUp rH

removeCombinationsWithHeight :: [Height] -> [[Person]] -> [[Person]]

-- removes lineUps that have the same height features

removeCombinationsWithHeight _ [] = []
removeCombinationsWithHeight ht (p:ps)

    | inList ht (extractCurrentHeightSet p) =
        removeCombinationsWithHeight ht ps
    | otherwise                    =
        p : removeCombinationsWithHeight ht ps

removeCombinationsWithoutHeight :: [Height] -> [[Person]] -> [[Person]]

-- remove lineUps that do not have the exact height features.

removeCombinationsWithoutHeight _ [] = []
removeCombinationsWithoutHeight ht (p:ps)

    | (sort ht) == (sort (extractCurrentHeightSet p)) =
        p : removeCombinationsWithoutHeight ht ps
    | otherwise                                       =
        removeCombinationsWithoutHeight ht ps


removeCombinationsWithoutAnyHeight :: [Height] -> [[Person]] -> [[Person]]

-- remove lineUps that do not have at least one height feature

removeCombinationsWithoutAnyHeight _ [] = []
removeCombinationsWithoutAnyHeight ht (p:ps)

    | inList ht (extractCurrentHeightSet p) =
        p : removeCombinationsWithoutAnyHeight ht ps
    | otherwise                    =
        removeCombinationsWithoutAnyHeight ht ps

removeParticularHeightCombination :: [Height] -> [[Person]] -> [[Person]]

-- remove lineups that have a particular set of heights.

removeParticularHeightCombination _ [] = []
removeParticularHeightCombination ht (p:ps)

    | (sort ht) == (sort (extractCurrentHeightSet p)) =
        removeParticularHeightCombination ht ps

    | otherwise =
        p : removeParticularHeightCombination ht ps

scoringInterpretationGenderAl ::
    (Int, Int) -> [Person] -> [[Person]] -> [[Person]]

scoringInterpretationGenderAl (pm, s) lineUp rm

    -- remove lineUps that have candidates in the list
    -- remove lineUps that have the same gender as in the list
    | pm == 0 && s == 0 = rM

    -- remove lineUps that do not have at least one of the
    -- gender feature in the list
    | pm == 0 && s == 1 =
        removeCombinationsWithoutAnyGender currentGenderSet rm

    -- remove lineUps that do not have the exact same genders as the
    -- list
    | pm == 0 && s == 2 =
        removeCombinationsWithoutGender currentGenderSet rm

    -- remove lineUps that have the exact combination of genders
    | pm == 1 && s == 0 =
        removeParticularGenderCombination currentGenderSet rm

    -- remove combinations that do not have the exact same genders as
    -- in the list
    | pm == 1 && s == 1 =
        removeCombinationsWithoutGender currentGenderSet rm

    where currentGenderSet = extractCurrentGenderSet lineUp
          rH = removeCombinationsWithGender currentGenderSet rm
          rM = removeCurrentCombinationFromList lineUp rH

removeCombinationsWithGender :: [Gender] -> [[Person]] -> [[Person]]

-- removes lineUps that have the same gender features

removeCombinationsWithGender _ [] = []
removeCombinationsWithGender g (p:ps)

    | inList g (extractCurrentGenderSet p) =
        removeCombinationsWithGender g ps
    | otherwise                            =
        p : removeCombinationsWithGender g ps

removeCombinationsWithoutGender :: [Gender] -> [[Person]] -> [[Person]]

-- remove lineUps that do not have the exact gender features.

removeCombinationsWithoutGender _ [] = []
removeCombinationsWithoutGender g (p:ps)

    | (sort g) == (sort (extractCurrentGenderSet p)) =
        p : removeCombinationsWithoutGender g ps
    | otherwise                                      =
        removeCombinationsWithoutGender g ps


removeCombinationsWithoutAnyGender :: [Gender] -> [[Person]] -> [[Person]]

-- remove lineUps that do not have at least one height feature

removeCombinationsWithoutAnyGender _ [] = []
removeCombinationsWithoutAnyGender g (p:ps)

    | inList g (extractCurrentGenderSet p) =
        p : removeCombinationsWithoutAnyGender g ps
    | otherwise                    =
        removeCombinationsWithoutAnyGender g ps

removeParticularGenderCombination :: [Gender] -> [[Person]] -> [[Person]]

-- remove lineups that have a particular set of gender

removeParticularGenderCombination _ [] = []
removeParticularGenderCombination g (p:ps)

    | (sort g) == (sort (extractCurrentGenderSet p)) =
        removeParticularGenderCombination g ps

    | otherwise =
        p : removeParticularGenderCombination g ps

scoringInterpretationColourAl ::
    (Int, Int) -> [Person] -> [[Person]] -> [[Person]]

scoringInterpretationColourAl (pm, s) lineUp rm

    -- remove lineUps that have candidates in the list
    -- remove lineUps that have the same colours as in the list
    | pm == 0 && s == 0 = rM

    -- remove lineUps that do not have at least one of the colours
    -- in the list
    | pm == 0 && s == 1 =
        removeCombinationsWithoutAnyColour currentColourSet rm

    -- remove lineUps that do not have the exact same colours as the
    -- list
    | pm == 0 && s == 2 =
        removeCombinationsWithoutColour currentColourSet rm

    -- remove lineUps that have the exact combination of colours
    | pm == 1 && s == 0 =
        removeParticularColourCombination currentColourSet rm

    -- remove combinations that do not have the exact same colours as
    -- in the list
    | pm == 1 && s == 1 =
        removeCombinationsWithoutColour currentColourSet rm

    where currentColourSet = extractCurrentHairColourSet lineUp
          rH = removeCombinationsWithColour currentColourSet rm
          rM = removeCurrentCombinationFromList lineUp rH

removeCombinationsWithColour :: [HairColour] -> [[Person]] -> [[Person]]

-- removes lineUps that have the same colour features

removeCombinationsWithColour _ [] = []
removeCombinationsWithColour hc (p:ps)

    | inList hc (extractCurrentHairColourSet p) =
        removeCombinationsWithColour hc ps
    | otherwise                            =
        p : removeCombinationsWithColour hc ps

removeCombinationsWithoutColour :: [HairColour] -> [[Person]] -> [[Person]]

-- remove lineUps that do not have the exact colour features.

removeCombinationsWithoutColour _ [] = []
removeCombinationsWithoutColour hc (p:ps)

    | (sort hc) == (sort (extractCurrentHairColourSet p)) =
        p : removeCombinationsWithoutColour hc ps
    | otherwise                                       =
        removeCombinationsWithoutColour hc ps

removeCombinationsWithoutAnyColour :: [HairColour] -> [[Person]] -> [[Person]]

-- remove lineUps that do not have at least one colour feature

removeCombinationsWithoutAnyColour _ [] = []
removeCombinationsWithoutAnyColour hc (p:ps)

    | inList hc (extractCurrentHairColourSet p) =
        p : removeCombinationsWithoutAnyColour hc ps
    | otherwise                             =
        removeCombinationsWithoutAnyColour hc ps

removeParticularColourCombination :: [HairColour] -> [[Person]] -> [[Person]]

-- remove lineups that have a particular set of colours.

removeParticularColourCombination _ [] = []
removeParticularColourCombination hc (p:ps)

    | (sort hc) == (sort (extractCurrentHairColourSet p)) =
        removeParticularColourCombination hc ps

    | otherwise =
        p : removeParticularColourCombination hc ps

inList :: Eq a => [a] -> [a] -> Bool

-- checks if elements in a list are present in the other list

inList [] y = False
inList (p:ps) y
    | elem p y  = True
    | otherwise = inList ps y


generateAllLineups :: [[Person]]

-- generate all possible candidate lineUps.

generateAllLineups =
    let heights     = [Short ..]
        hairColour  = [Blonde ..]
        gender      = [Male ..]
    in
    [ [p1,p2] |
    p1 <- [Person x y z | x <- heights, y <- hairColour, z <- gender],
    p2 <- [Person a b c | a <- heights, b <- hairColour, c <- gender],
    p1 /= p2 ]

generateCharacteristicCombinations :: CharacteristicSets

-- Generate all possible combinations of features and puts it
-- in a CharacteristicSet.

generateCharacteristicCombinations =
    let ht = [Short ..]
        hc = [Blonde ..]
        g  = [Male ..]

        height     = HT (nub [ sort [x,y] | x <- ht, y <- ht])
        hairColour = HC (nub [ sort [x,y] | x <- hc, y <- hc])
        gender     = G  (nub [ sort [x,y] | x <- g , y <- g ])
    in
    CS height hairColour gender

-- END Guess logics
