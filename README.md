# Minishell Project

![Minishell](https://github.com/8luerose/Minishell/assets/105616046/0575a315-f1c1-494b-b487-39ec5a486d22)

<br><br>



## 프로젝트 소개
Minishell은 Linux, Unix 시스템의 기본적인 shell, bash의 작동 원리를 이해하고 구현하는 프로그램입니다. 
<br><br>

## 프로젝트 목표
- 시스템 프로그래밍의 깊은 이해
- Bash 쉘의 기본 원리 및 작동 방식 습득
- C 언어를 이용한 효율적인 코드 작성 능력 향상
<br><br>

### 프로젝트 기간
2023.07.01 ~ 2023.09.17
<br><br>

## 주요 기능
1. 기본 쉘 명령의 실행
2. 파이프(`|`)를 이용한 명령어 체이닝
3. 내장 명령어 구현(`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`)
4. 환경 변수의 설정 및 제거
<br><br>

## 주요 사용 기술 및 도구
- C
- Bash
- Linux, Unix
- Makefile
<br><br>

## 작동 원리
이 프로젝트에서 구현된 minishell은 bash와 유사한 방식으로 작동합니다. 
사용자로부터 명령어를 입력 받아 파싱한 후, 적절한 시스템 호출을 통해 명령어를 실행합니다. 
파이프와 리다이렉션 기능을 통해 명령어 간의 데이터 흐름을 제어합니다.
<br><br>

### 파싱
사용자로부터 입력 받은 명령어를 공백, 특수 문자 등을 기준으로 토큰화하여 명령어, 옵션, 인자 등을 분리합니다.
<br>

### 실행
파싱된 결과를 바탕으로 fork와 execve 시스템 호출을 사용하여 프로세스를 생성하고 명령어를 실행합니다.
<br>

### 파이프와 리다이렉션
pipe 시스템 호출과 dup2 시스템 호출을 이용하여 프로세스 간의 데이터 흐름을 제어하고, 파일 디스크립터를 조작하여 입출력을 리다이렉트합니다.
<br><br>

## 설치 및 실행 방법
```sh
$ git clone [repository link]
$ cd minishell
$ make
$ ./minishell
```
<br><br>
## 주의 사항
해당 프로그램을 실행하기 위해서는 최신버전의 'readline' 이 설치되어있어야 합니다.


<img width="577" alt="스크린샷 2023-09-25 오전 3 26 47" src="https://github.com/8luerose/Minishell/assets/105616046/232a20f3-f049-4e2d-b097-6dda3e6c88fb">



