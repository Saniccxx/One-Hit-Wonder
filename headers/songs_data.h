#pragma once
#include <vector>
#include <string>

// ──────────────────────────────────────────────────────────────────────────────
// Pitch encoding — C major diatonic scale, transposed so that C is the root:
//   C=0  D=1  E=2  F=3  G=4  A=5  B=6  C'=7
//
// Duration unit: hundredths of a second (tempo ≈ 120 BPM)
//   Eighth note    =  25
//   Quarter note   =  50
//   Dotted quarter =  75
//   Half note      = 100
//   Dotted half    = 150
//   Whole note     = 200
//
// Each song contains exactly 3 melodic lines (phrases), concatenated into a
// single flat inner vector. Line boundaries are marked with comments.
// All songs are transposed into the C major diatonic set (0–7).
// ──────────────────────────────────────────────────────────────────────────────

inline const std::vector<std::string> song_names = {
    "Twinkle Twinkle Little Star",    // 0
    "Happy Birthday To You",           // 1
    "Jingle Bells",                    // 2
    "Ode to Joy",                      // 3
    "Amazing Grace",                   // 4
    "Mary Had a Little Lamb",          // 5
    "Row, Row, Row Your Boat",         // 6
    "When the Saints Go Marching In",  // 7
    "Yankee Doodle",                   // 8
    "London Bridge is Falling Down"    // 9
};

// notes[i] — pitch sequence for song i (three lines concatenated)
inline const std::vector<std::vector<int>> notes = {

    // ── 0. Twinkle Twinkle Little Star (Traditional, public domain) ──────────
    {   // Line 1: "Twinkle, twinkle, little star"
        0, 0, 4, 4, 5, 5, 4,
        // Line 2: "How I wonder what you are"
        3, 3, 2, 2, 1, 1, 0,
        // Line 3: "Up above the world so high, like a diamond in the sky"
        4, 4, 3, 3, 2, 2, 1
    },

    // ── 1. Happy Birthday To You (Traditional, public domain) ────────────────
    {   // Line 1: "Happy birthday to you"
        0, 0, 1, 0, 3, 2,
        // Line 2: "Happy birthday to you"
        0, 0, 1, 0, 4, 3,
        // Line 3: "Happy birthday, dear [Name] — happy birthday to you"
        0, 0, 7, 5, 3, 2, 1
    },

    // ── 2. Jingle Bells (J.L. Pierpont, 1857, public domain) — chorus ────────
    {   // Line 1: "Jingle bells, jingle bells,"
        2, 2, 2, 2, 2, 2,
        // Line 2: "Jingle all the way!"
        2, 4, 0, 1, 2,
        // Line 3: "Oh what fun it is to ride in a one-horse open sleigh!"
        3, 3, 2, 2, 1, 4
    },

    // ── 3. Ode to Joy (Beethoven, 1824, public domain) — main theme ──────────
    {   // Line 1: first phrase  (E E F G | G F E D)
        2, 2, 3, 4, 4, 3, 2, 1,
        // Line 2: resolution   (C C D E | E D D)
        0, 0, 1, 2, 2, 1, 1,
        // Line 3: third phrase (D D E C | D E F E D C)
        1, 1, 2, 0, 1, 2, 3, 2, 1, 0
    },

    // ── 4. Amazing Grace (John Newton, 1772, public domain) ──────────────────
    {   // Line 1: "Amazing grace, how sweet the sound"
        0, 4, 4, 2, 4, 2, 0,
        // Line 2: "That saved a wretch like me"
        0, 4, 4, 5, 4, 2,
        // Line 3: "I once was lost but now am found, was blind but now I see"
        2, 0, 2, 4, 2, 0
    },

    // ── 5. Mary Had a Little Lamb (Traditional, public domain) ───────────────
    {   // Line 1: "Mary had a little lamb"
        2, 1, 0, 1, 2, 2, 2,
        // Line 2: "Little lamb, little lamb"
        1, 1, 1, 2, 4, 4,
        // Line 3: "Mary had a little lamb, its fleece was white as snow"
        2, 1, 0, 1, 2, 2, 2, 1, 1, 2, 1, 0
    },

    // ── 6. Row, Row, Row Your Boat (Traditional, public domain) ──────────────
    {   // Line 1: "Row, row, row your boat"
        0, 0, 0, 1, 2,
        // Line 2: "Gently down the stream"
        2, 1, 2, 3, 4,
        // Line 3: "Merrily merrily merrily merrily, life is but a dream"
        7, 7, 7, 4, 4, 4, 2, 2, 2, 0, 4, 3, 2, 1, 0
    },

    // ── 7. When the Saints Go Marching In (Traditional, public domain) ────────
    {   // Line 1: "Oh when the saints"
        0, 2, 3, 4,
        // Line 2: "Oh when the saints"
        0, 2, 3, 4,
        // Line 3: "Go marching in — oh Lord, I want to be in that number"
        0, 2, 3, 4, 2, 0, 2, 4, 3, 2
    },

    // ── 8. Yankee Doodle (Traditional, public domain) — transposed to C ───────
    // Original key: G major.  Mapping: G→C(0) A→D(1) B→E(2) C→F(3) D→G(4) F#→B(6)
    {   // Line 1: "Yankee Doodle went to town, a-riding on a pony"
        0, 0, 1, 6, 0, 1, 2, 0,
        // Line 2: "Stuck a feather in his cap and called it macaroni"
        1, 2, 3, 2, 1, 0, 6, 0, 1, 2, 3, 1, 0,
        // Line 3: "Yankee Doodle keep it up, Yankee Doodle dandy"
        2, 2, 2, 0, 1, 2, 3
    },

    // ── 9. London Bridge is Falling Down (Traditional, public domain) ─────────
    {   // Line 1: "London Bridge is falling down"
        4, 5, 4, 3, 2, 3, 4,
        // Line 2: "Falling down, falling down"
        1, 2, 3, 2, 3, 4,
        // Line 3: "London Bridge is falling down, my fair lady"
        4, 5, 4, 3, 2, 4, 2, 0
    }
};

// durations[i] — note durations in hundredths of a second for song i
inline const std::vector<std::vector<int>> durations = {

    // ── 0. Twinkle Twinkle Little Star ───────────────────────────────────────
    {   // Line 1
        50, 50, 50, 50, 50, 50, 100,
        // Line 2
        50, 50, 50, 50, 50, 50, 100,
        // Line 3
        50, 50, 50, 50, 50, 50, 100
    },

    // ── 1. Happy Birthday To You ─────────────────────────────────────────────
    {   // Line 1  (dotted-eighth + sixteenth pickup)
        37, 13, 50, 50, 50, 100,
        // Line 2
        37, 13, 50, 50, 50, 100,
        // Line 3
        37, 13, 50, 50, 75, 25, 150
    },

    // ── 2. Jingle Bells ──────────────────────────────────────────────────────
    {   // Line 1
        50, 50, 100, 50, 50, 100,
        // Line 2
        50, 50, 50, 50, 200,
        // Line 3
        50, 50, 50, 50, 50, 100
    },

    // ── 3. Ode to Joy ────────────────────────────────────────────────────────
    {   // Line 1
        50, 50, 50, 50, 50, 50, 50, 100,
        // Line 2
        50, 50, 50, 75, 25, 50, 100,
        // Line 3
        50, 50, 50, 50, 50, 50, 50, 50, 50, 100
    },

    // ── 4. Amazing Grace (3/4 time) ──────────────────────────────────────────
    {   // Line 1
        50, 100, 75, 25, 100, 50, 150,
        // Line 2
        50, 100, 75, 25, 100, 150,
        // Line 3
        100, 50, 50, 150, 50, 200
    },

    // ── 5. Mary Had a Little Lamb ────────────────────────────────────────────
    {   // Line 1
        50, 50, 50, 50, 50, 50, 100,
        // Line 2
        50, 50, 100, 50, 50, 100,
        // Line 3
        50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 100
    },

    // ── 6. Row, Row, Row Your Boat ───────────────────────────────────────────
    {   // Line 1
        100, 100, 75, 25, 100,
        // Line 2
        75, 25, 75, 25, 200,
        // Line 3  (eighth-note triplet merrily run → quarter-note cadence)
        25, 25, 25, 25, 25, 25, 25, 25, 25, 50, 50, 50, 50, 50, 100
    },

    // ── 7. When the Saints Go Marching In ────────────────────────────────────
    {   // Line 1
        50, 50, 50, 100,
        // Line 2
        50, 50, 50, 100,
        // Line 3
        50, 50, 50, 100, 50, 50, 50, 50, 50, 100
    },

    // ── 8. Yankee Doodle ─────────────────────────────────────────────────────
    {   // Line 1
        50, 50, 50, 50, 50, 50, 50, 100,
        // Line 2
        50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 100,
        // Line 3
        50, 50, 50, 50, 50, 50, 100
    },

    // ── 9. London Bridge is Falling Down ─────────────────────────────────────
    {   // Line 1
        50, 50, 50, 50, 50, 50, 100,
        // Line 2
        50, 50, 100, 50, 50, 100,
        // Line 3
        50, 50, 50, 50, 100, 50, 50, 200
    }
};
