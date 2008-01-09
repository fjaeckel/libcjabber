/*
 * This file is part of libcjabber.
 *
 * cjabber is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * cjabber is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cjabber; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <openssl/sha.h>
#include <openssl/evp.h>

/* remove me */
#include <string.h>

char *create_sha_hash(char *data) {
  EVP_MD_CTX mdctx;
  const EVP_MD *md;
  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned int md_len;
  int i;

  OpenSSL_add_all_digests();
  
  md = EVP_get_digestbyname("sha1");

  EVP_MD_CTX_init(&mdctx);
  EVP_DigestInit_ex(&mdctx, md, NULL);
  EVP_DigestUpdate(&mdctx, data, strlen(data));
  EVP_DigestFinal_ex(&mdctx, md_value, &md_len);
  EVP_MD_CTX_cleanup(&mdctx);

  printf("SHA: ");
  for(i = 0; i < md_len; i++){
    printf("%02x", md_value[i]);
  }
  printf("\nmd_len: %d, i: %d\n",md_len, i);

  data=NULL;
  data=malloc(md_len);
  char buf[2];
  for(i = 0; i < md_len; i++){
    sprintf(buf, "%02x", md_value[i]);
    strcat(data,(char*) buf);
  }
  return data;
}
