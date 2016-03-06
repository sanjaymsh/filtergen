import glob

EnsureSConsVersion(0, 96)

VERSION = "0.13"

opts = Options()
opts.AddOptions(
	BoolOption('debug', 'debugging compiler options', 0),
    BoolOption('profiler', 'enable support for profiler', 0),
    BoolOption('gcov', 'enable test coverage with gcov', 0),
	)

env = Environment(options = opts)

warnings = ['',
			'all',
			'error',
			'aggregate-return',
			'cast-align',
			'cast-qual',
			'nested-externs',
			'shadow',
			'bad-function-cast',
			'write-strings',
            'init-self',
            'format=2', 
            'uninitialized',
            'pointer-arith',
            'strict-aliasing', 
]
for w in warnings:
	env.Append(CPPFLAGS='-W%s ' % (w,))

# Paired with -Wstrict-aliasing
if 'strict-aliasing' in warnings:
	env.Append(CPPLAGS='-fstrict-aliasing ')

# set the version
env.Append(CPPFLAGS = '-DVERSION=\\\"%s\\\" ' % (VERSION,))

# compile as GNU SOURCE to get strndup
env.Append(CPPFLAGS = '-D_GNU_SOURCE ')

Help(opts.GenerateHelpText(env))

if not env.GetOption("clean"):
	conf = Configure(env)
	if conf.CheckCHeader('getopt.h'):
		conf.env.Append(CPPFLAGS = '-DHAVE_GETOPT_H ')
	conf.CheckLib('getopt', 'getopt')

	if ARGUMENTS.get('profiler', 0):
		conf.CheckLib('profiler', 'ProfilerStart')

	if ARGUMENTS.get('gcov', 0):
		if conf.CheckLib('gcov'):
			env.Append(CFLAGS = '-fprofile-arcs -ftest-coverage ')

	env = conf.Finish()

if ARGUMENTS.get('debug', 0):
	env.Append(CPPFLAGS = '-g -O0 ')
else:
	env.Append(CPPFLAGS = '-O2 ')

DESTDIR = ARGUMENTS.get('DESTDIR', '')

sbindir = '/usr/sbin'
mandir = '/usr/share/man'
sysconfdir = '/etc/filtergen'
pkgdocdir = '/usr/share/doc/filtergen'
pkgexdir = pkgdocdir + '/examples'

filtergen  = env.Program('filtergen', ['filtergen.c',
									 'gen.c',
									 'filter.c',
									 'fg-util.c',
									 'fg-iptables.c',
									 'fg-ipchains.c',
									 'fg-ipfilter.c',
                                     'fg-iptrestore.c',
									 'fg-cisco.c',
									 'parser.y',
									 'scanner.l',
									 'glue.c',
									 'resolver.c',
									 'icmpent.c',
									 ])
env.SideEffect('parser.h', 'parser.c')

def sed(target, source, env):
	expandos = {
		'SYSCONFDIR': sysconfdir,
		'PKGEXDIR': pkgexdir,
		'SBINDIR': sbindir,
		'VERSION': VERSION
		}
	for (t, s) in zip(target, source):
		o = file(str(t), "w")
		i = file(str(s), "r")
		o.write(i.read() % expandos)
		i.close()
		o.close()
	return None

fgadm = env.Command('fgadm', 'fgadm.in', [sed, Chmod('fgadm', 0755)])

env.Command(['fgadm.conf', 'rules.filter'],
		  ['fgadm.conf.in', 'rules.filter.in'],
		  sed)

SConscript(['input/iptables/SConscript',
			't/SConscript'
			], 'env')

env.Install(DESTDIR + sbindir, [filtergen, fgadm])
bin = env.Alias('install-bin', DESTDIR + sbindir)

env.Install(DESTDIR + mandir + '/man5', 'filter_syntax.5')
man5 = env.Alias('install-man5', DESTDIR + mandir + '/man5')
env.Install(DESTDIR + mandir + '/man7', 'filter_backends.7')
man7 = env.Alias('install-man7', DESTDIR + mandir + '/man7')
env.Install(DESTDIR + mandir + '/man8', ['filtergen.8', 'fgadm.8'])
man8 = env.Alias('install-man8', DESTDIR + mandir + '/man8')
man = env.Alias('install-man', [man5, man7, man8])

env.Install(DESTDIR + sysconfdir, ['fgadm.conf', 'rules.filter'])
sysconf = env.Alias('install-sysconf', DESTDIR + sysconfdir)

env.Install(DESTDIR + pkgexdir, glob.glob('examples/*.filter'))
pkgex = env.Alias('install-examples', DESTDIR + pkgexdir)

env.Install(DESTDIR + pkgdocdir, glob.glob('doc/*'))
pkgdoc = env.Alias('install-doc', DESTDIR + pkgdocdir)

env.Install(DESTDIR + pkgdocdir, glob.glob('doc/*'))
pkgdoc = env.Alias('install-doc', DESTDIR + pkgdocdir)

env.Alias('install', [bin, man, sysconf, pkgdoc, pkgex])
