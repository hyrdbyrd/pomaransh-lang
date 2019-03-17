require('dotenv').config();

const colors = require('colors/safe');

const fs = require('fs');
const { resolve } = require('path');
const { spawn, exec } = require('child_process');

// Array.prototype.lastIem
// Array.prototype.lastIdx
Object.defineProperties(Array.prototype, {
    lastItem: {
        enumerable: false,
        get() {
            const len = this.length;
            if (len === 0) return undefined;

            return this[len - 1];
        }
    },
    lastIdx: {
        enumerable: false,
        get() {
            const len = this.length;
            if (len === 0) return 0;

            return len - 1;
        }
    }
});

// Recursive search
const findTests = inputPath => {
    const testFiles = [];
    const stack = [inputPath];

    while (stack.length) {
        const dir = stack.pop();

        fs.readdirSync(dir).forEach(foundPath => {
            // All C test files
            if (/\.test\.(c|h)(pp)?$/.test(foundPath))
                return testFiles.push(resolve(dir, foundPath));

            // Ignore node_modules
            if (/node_modules$/.test(foundPath))
                return;

            // If test not file (can be error with not extensioned files)
            if (!/\.[\w\d]*$/.test(foundPath))
                return stack.push(resolve(dir, foundPath));
        });
    }

    return testFiles;
};

const testCases = [];
const failedCompiles = [];

const trimLeft = str =>
    str
        .split('\n')
        .map(line => line.trimLeft())
        .join('\n');

const logResult = () => {
    failedCompiles.forEach(file => {
        console.error(`Error on comile: ${file}`);
    });

    let hasError = false;

    testCases.forEach(({ error, file, message, timeDiff, fileName }) => {
        const color = error ? 'red' : 'green';
        hasError = hasError || error;

        console.log(colors[color](trimLeft(`
            time: ${timeDiff}
            ${fileName}: ${message}
            path: ${file}
        `)));
    });

    if (hasError)
        process.exit(1);
    else
        process.exit(0);
}

const files = findTests(resolve(__dirname, process.env.SOURCE_PATH));
// Env from .env file
const { COMPILER, OPTIONS, OUT_EXTENSION } = process.env;

files.forEach((file, idx) => {
    const parsedPath = file.split('/').filter(Boolean);
    const fileName = parsedPath.lastItem.replace(/\.(c|h)(pp)?$/, `.${OUT_EXTENSION}`);

    const compileProcess = spawn(COMPILER, [OPTIONS, '-o', fileName, file]);

    compileProcess.on('exit', code => {
        if (code === 1)
            return failedCompiles.push(file);

        const startExec = Date.now();
        exec(`./${fileName}`, err => {
            const timeDiff = `${(Date.now() - startExec) / 1000}s.`;

            if (err)
                testCases.push({
                    file,
                    fileName,
                    error: true,
                    message: `Test Failed: ${err.message}`,
                    timeDiff
                });
            else
                testCases.push({
                    file,
                    fileName,
                    error: false,
                    message: `Test Passed`,
                    timeDiff
                });

            if (idx === files.lastIdx) logResult();
        });
    });
});
