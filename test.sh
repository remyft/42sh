#!zsh

TEST="coucou ca va"
TEST2="ca, va, bien"

ls LS$@LS
echo
ls LS"'$@'"LS
echo
ls "LS$@LS"
echo
ls LS$*LS
echo
ls LS"$*"LS
echo
ls "LS$*LS"
echo

ls ${TEST:+ x y z}
echo
ls "$TEST"
echo
ls LS$TEST-LS
echo
ls LS"$TEST"-LS
echo
ls "LS$TEST-LS"
echo

ls ${TEST2-x y z}
echo
ls "$TEST2"
echo
ls LS$TEST2-LS
echo
ls LS"$TEST2"-LS
echo
ls "LS$TEST2-LS"
echo
