git add -A

echo "Commit Message:"
read reason

git commit -m "$reason"

git push https://github.com/bezerrathm/ICG-FINAL-PROJECT.git master
