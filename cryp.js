//Collab with Mehul for particular this question

const bigInt = require('big-integer');

// RSA Parameters
const p = bigInt('100392089237316158323570985008687907853269981005640569039457584007913129640081');
const q = bigInt('90392089237316158323570985008687907853269981005640569039457584007913129640041');
const e = bigInt('65537');
const blockSize = 60;

// Calculate N and phi(N)
const N = p.multiply(q);
const phiN = p.subtract(1).multiply(q.subtract(1));

// Calculate d (modular multiplicative inverse of e mod phiN)
const d = e.modInv(phiN);

console.log('N:', N.toString());
console.log('d:', d.toString());

// Encrypt function
function encrypt(message) {
  const bytes = Buffer.from(message, 'utf8');
  let ciphertext = '';

  for (let i = 0; i < bytes.length; i += blockSize) {
    const block = bytes.slice(i, i + blockSize);
    const blockInt = bigInt(block.toString('hex'), 16);
    const encrypted = blockInt.modPow(e, N);
    const encryptedHex = encrypted.toString(16).padStart(2 * blockSize, '0');
    ciphertext += encryptedHex;
  }

  return ciphertext;
}

// Decrypt function
function decrypt(ciphertext) {
  let message = '';

  for (let i = 0; i < ciphertext.length; i += 2 * blockSize) {
    const block = ciphertext.slice(i, i + 2 * blockSize);
    const blockInt = bigInt(block, 16);
    const decrypted = blockInt.modPow(d, N);
    const decryptedBytes = Buffer.from(decrypted.toString(16), 'hex');
    message += decryptedBytes.toString('utf8');
  }

  return message;
}

// Message to encrypt
const message = 'Scaramouche, Scaramouche, will you do the Fandango? 💃🏽';

// Encryption
const ciphertext = encrypt(message);
console.log('Ciphertext:', ciphertext);

// Decryption
const decryptedMessage = decrypt(ciphertext);
console.log('Decrypted Message:', decryptedMessage);