import subprocess
import sys


def print_script(script):
    print(script, '> $')


def execute(flags: list[str] = None, **kwargs):
    if flags is None:
        flags = []
    for key, value in kwargs.items():
        flags.append(f'{key}={value}')

    script = f'gen ' + ' '.join(flags)
    result = subprocess.run(['./gen'] + flags, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    error = result.stderr.decode()
    if result.returncode != 0:
        print('Error occured inside generator.')
        print(f'script: {script}')
        print(error)
        sys.exit(1)

    return error, script, result


def create_script(flags: list[str] = None, **kwargs):
    return execute(flags, **kwargs)[1]


def merge_scripts(scripts: list[str] = None, stdout_run=subprocess.PIPE):
    scripts_flag = []
    for i in range(len(scripts)):
        scripts_flag.append(' '.join(scripts[i].split(' ')[1:]))
    script = f'gen ' + ' T '.join(scripts_flag)

    result = subprocess.run(['./gen'] + script.split()[1:], stdout=stdout_run, stderr=subprocess.PIPE)
    error = result.stderr.decode()
    if result.returncode != 0:
        print('Error occured inside generator.')
        print(f'script: {script}')
        print(error)
        sys.exit(1)

    return script, result


class MultiTest:
    def __init__(self):
        self.scripts = []

    def add_script(self, flags: list[str] = None, **kwargs):
        self.scripts.append(create_script(flags, **kwargs))

    def make(self):
        return merge_scripts(self.scripts)[0]

    def print(self):
        print_script(self.make())
        print('<#--\nmade from:\n' + '\n'.join(self.scripts) + '\n-->')

    def write_test(self, filename):
        with open(filename, "w") as f:
            merge_scripts(self.scripts, f)


if __name__ == '__main__':
    test0 = MultiTest()
    test0.add_script(mode='anime')

    test0.print()

    test1 = MultiTest()
    test1.add_script(['shuffle'], mode='random', n=10, slen=50)
    test1.add_script(mode='pal', n=10, slen=33, alen=15)
    test1.add_script(mode='random', n=50, slen=50, alph=4)
    test1.add_script(['shuffle'], mode='random', n=1, slen=250)
    test1.add_script(['shuffle'], mode='thue', slen=228, alen=45, alph=3)
    test1.add_script(mode='pal', n=20, slen=279, alen=341)

    test1.print()

    test2 = MultiTest()
    test2.add_script(mode='pal', n=45, slen=551, alen=228)
    test2.add_script(mode='pal', n=100, slen=523, alen=505)
    test2.add_script(mode='pal', n=100, slen=644, alen=710)
    test2.add_script(mode='pal', n=100, slen=1240, alen=2604)
    test2.add_script(mode='pal', n=50, slen=1894, alen=975)
    test2.add_script(['shuffle'], mode='random', n=1000, slen=5000)
    test2.add_script(['shuffle'], mode='random', n=2500, slen=6000, alph=3)
    test2.add_script(mode='pal', n=3000, slen=5231, alen=5604)
    test2.add_script(mode='pal', n=5000, slen=10438, alen=15023)
    test2.add_script(mode='random', n=13000, slen=13000, alph=3)
    test2.add_script(['shuffle'], mode='random', n=1, slen=200000, alph=2)
    test2.add_script(['shuffle'], mode='thue', slen=55031, alen=45028, alph=3)
    test2.add_script(mode='pal', n=3000, slen=50231, alen=44596, alph=4)
    test2.add_script(mode='pal', n=10000, slen=89249, alen=67645, alph=3)

    test2.print()

    test0.write_test("00.txt")
    test1.write_test("01.txt")
    test2.write_test("02.txt")
