# 현재 디렉토리 이름을 CMakeLists의 프로젝트 명으로 치환
projectName=$(pwd | sed 's/^.*\/\(.*$\)/\1/')

sed -i '' "s/helloCV/${projectName}/g" CMakeLists.txt
